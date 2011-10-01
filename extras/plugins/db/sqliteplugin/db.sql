/*
* remove second ; for manual usage
*/
PRAGMA synchronous = OFF;;
PRAGMA temp_store = MEMORY;;
PRAGMA quick_check;;
PRAGMA journal_mode =  MEMORY;;

CREATE TABLE articles (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "title" TEXT,
    "content" TEXT,
    "author" VARCHAR(150),
    "published" DATETIME,
    "md5" TEXT,
    "guid" TEXT,
    "catid" NUMERIC NOT NULL CONSTRAINT fk_bookcat_id REFERENCES bookcat(id) ON DELETE CASCADE,
    "synch_state" INTEGER  NOT NULL  DEFAULT (0)
);;

CREATE TABLE bookcat (
  "id" INTEGER PRIMARY KEY AUTOINCREMENT, 
  "name" VARCHAR(120), 
  "parent" INTEGER default 0,
  "synch_state" INTEGER  NOT NULL  DEFAULT (0)
);;

CREATE TRIGGER fkd_articles_bookcat_id
 BEFORE DELETE ON bookcat
 FOR EACH ROW BEGIN
      DELETE from articles WHERE articles.catid = OLD.id;
 END;;
CREATE TABLE articles_backup (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "title" TEXT,
    "content" TEXT,
    "author" VARCHAR(150),
    "published" DATETIME,
    "md5" TEXT,
    "guid" TEXT,
    "catid" NUMERIC,
    "synch_state" INTEGER  NOT NULL  DEFAULT (0)
);;

CREATE TABLE bookcat_backup (
  "id" INTEGER PRIMARY KEY AUTOINCREMENT, 
  "name" VARCHAR(120), 
  "parent" INTEGER default 0,
  "synch_state" INTEGER  NOT NULL  DEFAULT (0)
);;