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
    CREATE TABLE clients(ID VARCHAR(16) NOT NULL PRIMARY KEY, UNAME VARCHAR(255) NOT NULL,
    publicKey VARCHAR(128), LastSeen VARCHAR(16));
    """) 
    x=c.execute('SELECT * FROM clients')
    for row in x:
        print(row)
    c.execute("""
    CREATE TABLE messages(ID INTEGER NOT NULL PRIMARY KEY,
    ToClient VARCHAR(16), FromClient VARCHAR(16),
    Type VARCHAR(1), Content BLOB);
    """) 
    conn.commit()
    conn.close()


