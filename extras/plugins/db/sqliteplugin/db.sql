PRAGMA synchronous = OFF;
PRAGMA temp_store = MEMORY;
PRAGMA quick_check; 
PRAGMA journal_mode =  MEMORY;

CREATE TABLE aticles (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  title TEXT UNIQUE,
  content TEXT ,
  author VARCHAR(150) ,
  published DATETIME,
  md5 TEXT,
  catid NUMERIC
);
/*
CREATE TABLE general (
    bookname TEXT,
    descr text,
    hash text,
    articles int
);
*/
CREATE TABLE bookcat (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  name VARCHAR(120), 
  description TEXT,
  parent int default 0,
  subcat int default 0
);