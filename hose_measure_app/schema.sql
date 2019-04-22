drop table if exists entries;
create table entries (
  id integer primary key autoincrement,
  medida integer not null,
  color text not null
);
create table listas (
  id integer not null,
  medida integer not null,
  color text not null
);