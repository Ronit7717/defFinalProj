import sqlite3

conn = sqlite3.connect('server.db') 
conn.text_factory = bytes
conn.executescript("""
CREATE TABLE clients(ID BIT(128) NOT NULL PRIMARY KEY,
publicKey BIT(256), LastSeen DATETIME);
""") 
conn.executescript("""
CREATE TABLE messages(ID BIT(32) NOT NULL PRIMARY KEY,
ToClient BIT(128), FromClient BIT(128),
Type BIT(8), Content BLOB);
""") 