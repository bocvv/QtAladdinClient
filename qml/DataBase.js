
function dbInit()
{
    var db = LocalStorage.openDatabaseSync("mySQLite", "1.0", "This is only for demo", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS myclass (name text, teacher text)')
        })
        console.log("Table Created!")
    } catch (err) {
        console.log("Error creating table in database: " + err)
    };
}

function dbGetHandle()
{
    try {
        var db = LocalStorage.openDatabaseSync("mySQLite", "1.0", "This is only for demo", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

function dbInsert(name, teacher)
{
    var db = dbGetHandle()
    var rowid = 0;
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO myclass VALUES(?, ?)',
                      [name, teacher])
        var result = tx.executeSql('SELECT last_insert_rowid()')
        rowid = result.insertId
    })
    return rowid;
}

function dbReadLastReport()
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var result = tx.executeSql(
                    'select * from status_report order by id desc limit 0,1')
        $play_phone_rate = result.rows.item(0).play_phone
        $look_lamp_rate = result.rows.item(0).look_lamp
        $look_monitor_rate = result.rows.item(0).look_monitor
        $look_book_rate = result.rows.item(0).look_book
        $look_other_rate = result.rows.item(0).look_other
        $look_none_rate = result.rows.item(0).look_none
    })
}

function dbReadAll()
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql(
                    'SELECT rowid,name,teacher FROM myclass order by rowid desc')
        for (var i = 0; i < results.rows.length; i++) {
            listModel.append({
                                 id: results.rows.item(i).rowid,
                                 name: results.rows.item(i).name,
                                 teacher: results.rows.item(i).teacher
                             })
        }
    })
}

function dbUpdate(name, teacher,Prowid)
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql(
                    'update myclass set name=?, teacher=? where rowid = ?', [name, teacher,Prowid])
    })
}

function dbDeleteRow(Prowid)
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql('delete from myclass where rowid = ?', [Prowid])
    })
}

