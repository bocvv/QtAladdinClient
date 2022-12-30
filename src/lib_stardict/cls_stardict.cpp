/*************************************************************************
 * libStarDict - A C++ library to read stardict files
 * Copyright (C) 2013  S.M.Mohammadzadeh <mehran.m@aut.ac.ir>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *************************************************************************/
/**
 @author S.Mohammad M. Ziabary <mehran.m@aut.ac.ir>
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "cls_stardict.h"
#include "Private/clsStarDict_p.h"

using namespace std;

ClsSDict::ClsSDict() {
    this->pPrivate = new clsSDictPrivate();
}

std::pair<string, int> split(const string& str, const string& delim) {
    string::size_type position;
    position = str.find(delim);

    string key = str.substr(0, position);
    int value = stol(str.substr(position + 1, str.length() - position - 1));

    return make_pair(key, value);
}

void ClsSDict::read_typo_txt(string& typo_txt_path) {
    //根据key从文件中读出相应的value
    ifstream ous(typo_txt_path.c_str());
    while(!ous.eof()){
        string str_line;
        std::getline(ous, str_line);

        if (str_line.empty()) {
            continue;
        }

        string delim = " ";
        pair<string, int> iter = split(str_line, delim);
        typo_map.insert(iter); //将字符串转换为键值对
    }
}

std::string ClsSDict::fuzzy_lookup_withtypo(std::string& _phrase) {
    gchar *res[10];
    gint dist_res[10];
    const size_t res_size = sizeof(res) / sizeof(gchar *);
    bool has_fuzzy = this->pPrivate->LookupWithFuzzy(_phrase.c_str(), res, dist_res, res_size);

    int max_prob{0};
    std::string most_similar_word;
    for (int i = 0; i < res_size; i++) {
        if (res[i] == NULL) {
            break;
        }

        std::string key = res[i];
        int prob;
        // 如果该单词不在typo词表则赋值频次为30000
        if (typo_map.find(key) == typo_map.end()) {
            prob = 30000 / dist_res[i];
        } else {
            prob = typo_map[key] / dist_res[i];
        }

        if (prob > max_prob) {
            most_similar_word = key;
            max_prob = prob;
        }
    }

    if (most_similar_word.empty() && res[0] != NULL) {
        // directly use the first result word to return
        most_similar_word = res[0];
    }

    // release the memory used by res
    std::for_each(res, res+res_size, g_free);

    _phrase = most_similar_word;
    if (most_similar_word.empty()) {
        return most_similar_word;
    }

    return lookup(most_similar_word);
}

std::string ClsSDict::fuzzy_lookup(std::string& _phrase, bool with_typo) {
    if (!with_typo) {
        gchar *res[2];
        gint distlist[2];
        const size_t res_size = sizeof(res) / sizeof(gchar *);
        bool has_fuzzy = this->pPrivate->LookupWithFuzzy(_phrase.c_str(), res, distlist, res_size);

        std::string first_fuzzy_res;
        if (has_fuzzy) {
            // cal most similar word
            first_fuzzy_res = res[0];
        }

        std::for_each(res, res+res_size, g_free);
        return first_fuzzy_res;
    } else {
        return fuzzy_lookup_withtypo(_phrase);
    }
}

std::string ClsSDict::lookup(const std::string& _phrase, bool _json) {
    (void)_json;
    std::string Result;
    if (_phrase[0]=='\0')
        return Result;

    SearchResultList_t res_list;

    this->pPrivate->SimpleLookup(_phrase, res_list);
    if (!res_list.empty()) {
        for (SearchResultIter ptr=res_list.begin(); ptr!=res_list.end(); ++ptr)
        {
            Result = (ptr)->exp.substr(1);
            break;
        }
    }
    return Result;
}

void ClsSDict::load_dics(const std::string& _dicDir) {
    strlist_t dicts_dir_list;
    dicts_dir_list.push_back(_dicDir);

    strlist_t empty_list;
    this->pPrivate->load(dicts_dir_list, empty_list, empty_list);
}


