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

#ifndef LIBSDICT_H
#define LIBSDICT_H

#include <string>
#include <unordered_map>


class clsSDictPrivate;
class ClsSDict
{
public:
    ClsSDict();

    void load_dics(const std::string& _dicDir);
    std::string lookup(const std::string& _phrase, bool _json = true);
    std::string fuzzy_lookup(std::string& _phrase, bool with_typo = true);
    std::string fuzzy_lookup_withtypo(std::string& _phrase);

    void read_typo_txt(std::string& typo_txt_path);

private:
    clsSDictPrivate* pPrivate;
    std::unordered_map<std::string, int> typo_map;
};

#endif // LIBSDICT_H
