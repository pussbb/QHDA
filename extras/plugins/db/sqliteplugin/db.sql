/*
* remove second ; for manual usage
*/
PRAGMA synchronous = OFF;;
PRAGMA temp_store = MEMORY;;
PRAGMA quick_check;;
PRAGMA journal_mode =  MEMORY;;

CREATE TABLE articles (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "title" TEXT,
    "content" TEXT,
    "author" VARCHAR(150),
    "published" DATETIME,
    "md5" TEXT,
    "guid" TEXT,
    "catid" NUMERIC NOT NULL CONSTRAINT fk_bookcat_id REFERENCES bookcat(id) ON DELETE CASCADE
);;

CREATE TABLE bookcat (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  name VARCHAR(120), 
  parent int default 0
);;

CREATE TRIGGER fkd_articles_bookcat_id
 BEFORE DELETE ON bookcat
 FOR EACH ROW BEGIN
      DELETE from articles WHERE articles.cat_id = OLD.id;
 END;;