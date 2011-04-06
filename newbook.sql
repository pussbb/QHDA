     QSqlQuery query;
     query.exec("create table general ("
                "bokname text, descr text,hash text,articles int)");
     query.exec("create table bookcat (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name varchar(20), descr text,parent int default 0, subcat int default 0)");
     query.exec("create table articles (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name text, body text,author varchar(50),pdate DATE,md5 text,catid int)");
