import sqlite3


def CreateTables():
    print('create them, oh man')
    file_name = 'server.db'
    f = open(file_name, 'a+') 
    f.close()
    conn = sqlite3.connect('server.db') 
    conn.text_factory = bytes
    c = conn.cursor()
    c.execute("""
    CREATE TABLE clients(ID BIT(128) NOT NULL PRIMARY KEY, UNAME BIT(256) NOT NULL,
    publicKey BIT(256), LastSeen DATETIME DEFAULT (datetime('now','localtime')));
    """) 
    x=c.execute('SELECT * FROM clients')
    for row in x:
        print(row)
    c.execute("""
    CREATE TABLE messages(ID BIT(32) NOT NULL PRIMARY KEY,
    ToClient BIT(128), FromClient BIT(128),
    Type BIT(8), Content BLOB);
    """) 
    conn.commit()
    conn.close()


