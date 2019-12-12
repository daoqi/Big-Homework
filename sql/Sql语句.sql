drop database if exists bighomework;
set character_set_database=gbk;
create database bighomework;
use bighomework;
drop table if exists userlist;
create table userlist
	(
		id int auto_increment primary key,
		usn char(75) not null,
		psd char(80) not null,
		state int not null
	);
drop table if exists goodslist;
create table goodslist
	(
		gid int auto_increment primary key,
		gname char(80) not null,
		price double not null,
		logid int not null
	);

drop table if exists log;
create table log
	(
		lid int auto_increment primary key,
		gname char(80) not null,
		price double not null,
		in_time datetime,
		out_time datetime
	);

drop table if exists keyword;
create table keyword
	(
		kid int auto_increment primary key,
		kname char(80) not null
	);

    



insert into userlist(usn,psd,state) values
	('zzz',password('123'),0),
	('wz',password('123456'),0),
	('zzh',password('123'),1)
	 ; 
/*
insert into goodslist(gname,price) values
	('农夫山泉',3.0);

      

insert into log(gname,price,in_time,out_time) values
	('农夫山泉',3.0,current_date(),null);




select * from log where month(out_time) = month(now()) and day(out_time) = day(now())
*/