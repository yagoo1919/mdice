#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <set>
#include "EncodingConvert.h"
#include "cqsdk.h"
#include "database.h"
#include <map>
#include <DiceMsgSend.h>
namespace database
{
	QString st2qst(const std::string str)
	{
		return QString::fromLocal8Bit(str.data());
	}
	common::tool::StringTool tool;
	int hiy_callback(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string piece = value[2];
		std::string piece2 = UTF8toGBK(piece);
		*(std::string*)tem_string = piece2;
		return 1;
	}
	int banlist_callback(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string note = value[2];
		std::string code = value[0];
		std::string id = value[1];
		std::string iferase = value[3];
		iferase = iferase == "0" ? "未消除" : "已消除";
		std::string note2 = UTF8toGBK(note);
		std::string id2 = UTF8toGBK(id);
		std::string code2 = UTF8toGBK(code);
		*(std::string*)tem_string += "\n————\n#ID:" + id2 + "\n#条目号:\n" + code2 + "\n#备注:\n" + note2 + "\n#状态:" + iferase;
		return 0;
	}
	int banlist_callbackqq(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string id = value[1];
		std::string id2 = UTF8toGBK(id);
		*(std::string*)tem_string += id2;
		AddMsgToQueue(Dice::DiceMsg("112", 0ll, 2918762900, Dice::MsgType::Private));
		return 0;
	}
	int maymatch_callback(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string piece = value[1];
		std::string piece2 = UTF8toGBK(piece);
		std::vector<std::string>* temmsg = NULL;
		temmsg = (std::vector<std::string>*)tem_string;
		temmsg->push_back(piece2);
		if (temmsg->size() >= 8)
			return 1;
		else return 0;
	}
	int hiy_callbackall(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string piece1 = value[1];
		std::string piece1_2 = UTF8toGBK(piece1);
		std::string piece2 = value[2];
		std::string piece2_2 = UTF8toGBK(piece2);
		std::map<const std::string, std::string>* temmsg = NULL;
		temmsg = (std::map<const std::string, std::string>*)tem_string;
		temmsg->insert(std::pair<const std::string, std::string>(piece1_2, piece2_2));
		return 0;
	}
	int myreply_callback_partreply(void* tem_reply, int argc, char* value[], char* name[])
	{
		std::string piece1 = value[2];
		std::string piece1_2 = UTF8toGBK(piece1);
		std::string piece2 = value[7];
		std::string piece2_2 = UTF8toGBK(piece2);
		std::map<const std::string, std::string>* temmsg = NULL;
		temmsg = (std::map<const std::string, std::string>*)tem_reply;
		temmsg->insert(std::pair<const std::string, std::string>(piece1_2, piece2_2));
		return 0;
	}
	int myreply_callback(void* tem_reply, int argc, char* value[], char* name[])
	{
		std::string piece1 = value[1];
		piece1 = UTF8toGBK(piece1);
		std::string piece2 = value[2];
		piece2 = UTF8toGBK(piece2);
		int piece3 = stoi((string)value[3]);
		std::string piece4 = value[4];
		piece4 = UTF8toGBK(piece4);
		int piece5 = stoi((string)value[5]);
		int piece6 = stoi((string)value[6]);
		int piece7 = stoi((string)value[7]);
		struct replyinfo* temmsg = NULL;
		temmsg = (struct replyinfo*)tem_reply;
		temmsg->replymsg = piece1;
		temmsg->signal = piece2;
		temmsg->type = piece3;
		temmsg->group = piece4;
		temmsg->timelimit = piece5;
		temmsg->timeperday = piece6;
		temmsg->matchtype = piece7;
		return 1;
	}
	int eventreply_callback(void* tem_reply, int argc, char* value[], char* name[])
	{
		std::string pocess = value[1];
		pocess = UTF8toGBK(pocess);
		int delay = stoi((string)value[2]);
		std::string events = value[0];
		events = UTF8toGBK(events);
		struct eventinfo* temmsg = NULL;
		temmsg = (struct eventinfo*)tem_reply;
		temmsg->process = pocess;
		temmsg->dealy = delay;
		temmsg->eventname = events;
		return 1;
	}
	int myreply_callbackall(void* tem_reply, int argc, char* value[], char* name[])
	{
		Ui::Myreply* reply_data = NULL;
		reply_data = (Ui::Myreply*)tem_reply;
		int row_count = reply_data->tableWidget->rowCount();
		reply_data->tableWidget->setRowCount(row_count + 1);
		reply_data->tableWidget->setVerticalHeaderItem(row_count + 1, new QTableWidgetItem(QString::number(row_count)));
		for (int i = 1; i < 8; i++)
		{
			reply_data->tableWidget->setItem(row_count - 1, i - 1, new QTableWidgetItem(st2qst(UTF8toGBK((string)value[i]))));
		}
		return 0;
	}
	int eventreply_callbackall(void* tem_reply, int argc, char* value[], char* name[])
	{
		database::eventinfo temp_info;
		std::string pocess = value[1];
		pocess = UTF8toGBK(pocess);
		int delay = stoi((string)value[2]);
		std::string events = value[0];
		events = UTF8toGBK(events);
		temp_info.dealy = delay;
		temp_info.eventname = events;
		temp_info.process = pocess;
		std::map<const std::string, database::eventinfo>* temmsg = NULL;
		temmsg = (std::map<const std::string, database::eventinfo>*)tem_reply;
		temmsg->insert({ temp_info.eventname, temp_info });
		return 0;
	}
	int hiy_callbackallFQT(void* tem_reply, int argc, char* value[], char* name[])
	{
		Ui::Myreply* reply_data = NULL;
		reply_data = (Ui::Myreply*)tem_reply;
		int row_count = reply_data->tableWidget_2->rowCount();
		reply_data->tableWidget_2->setRowCount(row_count + 1);
		reply_data->tableWidget_2->setItem(row_count - 1, 0, new QTableWidgetItem(st2qst(UTF8toGBK((string)value[1]))));
		reply_data->tableWidget_2->setItem(row_count - 1, 1, new QTableWidgetItem(st2qst(UTF8toGBK((string)value[2]))));
		return 0;
	}
	int myreply_callback_recorder(void* tem_reply, int argc, char* value[], char* name[])
	{
		pair<long long, int>* reply = NULL;
		reply = (pair<long long, int>*)tem_reply;
		std::string piece = value[2];
		string piece2 = GBKtoUTF8(piece);
		if (piece2.empty())piece2 = "0";
		reply->first = stoll(piece);
		reply->second = stoi((string)value[3]);
		return 1;
	}
	int list_callback(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string piece = value[0];
		std::string piece2 = value[1];
		std::string piece_trans = UTF8toGBK(piece);
		std::string piece_trans2 = UTF8toGBK(piece2);
		*(std::string*)tem_string += "\n" + piece_trans + ":" + piece_trans2 + "条";
		return 0;
	}
	int index_callback(void* tem_string, int argc, char* value[], char* name[])
	{
		std::string piece = value[1];
		std::string piece_trans = UTF8toGBK(piece);
		*(std::string*)tem_string += piece_trans + "、";
		return 0;
	}
	void hiy::create_table(sqlite3* olt_db, string tablename)
	{
		int rc = 0;
		char* err_msg = NULL;
		char sql[150];
		char temp_msg[150];
		sprintf(sql, "CREATE TABLE IF NOT EXISTS %s(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT NOT NULL UNIQUE,TXT TEXT NOT NULL);", tablename.c_str());
		rc = sqlite3_exec(olt_db, sql, NULL, NULL, &err_msg);
	}
	void hiy::insert(std::string a, std::string b, std::string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		char temp_msg[5000];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string tablename2 = GBKtoUTF8(tablename);
		create_table(olt_db, tablename2);
		std::string a2 = GBKtoUTF8(a);
		std::string b2 = GBKtoUTF8(b);
		sprintf(temp_msg, "insert into %s(name,txt) values('%s','%s');", tablename2.c_str(), a2.c_str(), b2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		if (rc == 19)
		{
			char temp_msg_2[5000];
			sprintf(temp_msg_2, "UPDATE %s set txt= '%s' where name='%s';", tablename2.c_str(), b2.c_str(), a2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg_2, NULL, NULL, &err_msg);
		}
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void hiy::quickinsert(std::map<const std::string, std::string>* b, std::string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		char temp_msg[5000];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string tablename2 = GBKtoUTF8(tablename);
		create_table(olt_db, tablename2);
		for (auto each : *b)
		{
			std::string a2 = GBKtoUTF8(each.first);
			std::string b2 = GBKtoUTF8(each.second);
			sprintf(temp_msg, "insert into %s(name,txt) values('%s','%s');", tablename2.c_str(), a2.c_str(), b2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
			if (rc == 19)
			{
				char temp_msg_2[5000];
				sprintf(temp_msg_2, "UPDATE %s set txt= '%s' where name='%s';", tablename2.c_str(), b2.c_str(), a2.c_str());
				rc = sqlite3_exec(olt_db, temp_msg_2, NULL, NULL, &err_msg);
			}
		}
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void hiy::get(std::string txt, string& reply, string title, char* position, bool type)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		create_table(olt_db, title2);
		sprintf(temp_msg, "select * from %s where name='%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		if (tem_string2.empty())
		{
			char temp_msg_2[300];
			sprintf(temp_msg_2, "select * from %s where name like '%%%s%%'", title2.c_str(), txt2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg_2, hiy_callback, tem_string, &err_msg);
			std::string tem_string3 = *tem_string;
			if (!tem_string3.empty())
			{

				std::vector<std::string>* vector = new std::vector<std::string>;
				rc = sqlite3_exec(olt_db, temp_msg_2, maymatch_callback, vector, &err_msg);
				*tem_string += "\n模糊匹配到以下条目:";
				for (auto each : *vector)
				{
					*tem_string += "\n" + each;
				}
			}
		}
		sqlite3_close(olt_db);
		reply = *tem_string;
		delete(tem_string);
	}
	void hiy::getall(std::map<const std::string, std::string>* b, std::string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		create_table(olt_db, title2);
		sprintf(temp_msg, "select * from %s", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callbackall, b, &err_msg);
		sqlite3_close(olt_db);
	}
	void hiy::getallFQT(string title, char* position, Ui::Myreply* replyp)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		sprintf(temp_msg, "select * from %s", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callbackallFQT, replyp, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void hiy::del(std::string txt, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[1000];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		create_table(olt_db, title2);
		sprintf(temp_msg, "delete from %s where name='%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		std::string a = temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void hiy::era(std::string txt, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[150];
		std::string txt2 = GBKtoUTF8(txt);
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		sprintf(temp_msg, "DROP TABLE %s;", txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void hiy::list(string& reply, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		rc = sqlite3_exec(olt_db, "select * from sqlite_sequence", list_callback, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		sqlite3_close(olt_db);
		reply += *tem_string;
		delete(tem_string);
	}
	void hiy::index(std::string& index, std::string  title, int page, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string title2 = GBKtoUTF8(title);
		create_table(olt_db, title2);
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		sprintf(temp_msg, "select * from %s where ID > %d and ID < %d  ", title2.c_str(), page * 40, page * 40 + 40);
		rc = sqlite3_exec(olt_db, temp_msg, index_callback, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		sqlite3_close(olt_db);
		index += *tem_string;
		delete(tem_string);
	}
	void myreply::del(std::string txt, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[100];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		sprintf(temp_msg, "delete from %s where signal='%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void myreply::create_table(string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		char* err_msg = NULL;
		char* sql = new char[300];
		char* temp_msg = new char[300];
		std::string title2 = GBKtoUTF8(tablename);
		sprintf(sql, "CREATE TABLE IF NOT EXISTS %s(ID INTEGER PRIMARY KEY AUTOINCREMENT,reply TEXT NOT NULL,signal TEXT NOT NULL UNIQUE,type INT NOT NULL,groupid TEXT,timelimit INT,timeperday INT,matchtype INT);", title2.c_str());
		rc = sqlite3_exec(olt_db, sql, NULL, NULL, &err_msg);
		sprintf(temp_msg, "insert into %s(reply,signal,type,groupid,timelimit,timeperday,matchtype) values('initttt','//this is init msg',0,'0',0,0,0); ", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
		delete[]sql;
		delete[]temp_msg;
	}
	void myreply::create_table_record(char* position)
	{
		sqlite3* olt_db = NULL;
		char* err_msg = NULL;
		int rc = 0;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		rc = sqlite3_exec(olt_db, "CREATE TABLE IF NOT EXISTS recorder(signal TEXT NOT NULL UNIQUE,usetimes TEXT,usetime INT);", NULL, NULL, &err_msg);
		rc = sqlite3_exec(olt_db, "insert into recorder(signal,usetimes,usetime) values('//intmsg//','0',0); ", NULL, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void myreply::era(std::string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[150];
		std::string txt2 = GBKtoUTF8(title);
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		sprintf(temp_msg, "DELETE from %s;", txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void myreply::get_record(std::string txt, std::pair<long long, int>* reply, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[3000];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string txt2 = GBKtoUTF8(txt);
		sprintf(temp_msg, "select * from recorder where signal='%s'", txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, myreply_callback_recorder, reply, &err_msg);
		sqlite3_close(olt_db);
	}
	void myreply::update_record(std::string signal, std::pair<long long, int>* reply, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		char* err_msg1 = new char[300];
		std::string tablename = GBKtoUTF8(to_string(reply->first));
		std::string signal2 = GBKtoUTF8(signal);
		char* temp_msg = new char[300];
		sprintf(temp_msg, "replace into recorder(signal,usetimes,usetime) values('%s','%s',%d);",
			signal2.c_str(), tablename.c_str(), reply->second);
		rc = sqlite3_exec(olt_db, "replace into recorder(signal,usetimes,usetime) values('12','1111111',1);", NULL, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
		delete[]temp_msg;
	}
	void myreply::insert(database::replyinfo* data, std::string tablename, char* position)

	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		char* err_msg1 = new char[300];
		std::string tablename2 = GBKtoUTF8(tablename);
		std::string signal2 = GBKtoUTF8(data->signal);
		std::string reply2 = GBKtoUTF8(data->replymsg);
		std::string group2 = GBKtoUTF8(data->group);
		char* temp_msg = new char[3000];
		sprintf(temp_msg, "insert into %s(reply,signal,type,groupid,timelimit,timeperday,matchtype) values('%s','%s',%d,'%s',%d,%d,%d);",
			tablename2.c_str(), reply2.c_str(), signal2.c_str(), data->type, group2.c_str()
			, data->timelimit, data->timeperday, data->matchtype);
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		if (rc == 19)
		{
			char* temp_msg_2 = new char[3000];
			sprintf(temp_msg_2, "UPDATE %s set reply= '%s',type= %d,groupid= '%s',timelimit= %d,timeperday= %d,matchtype= %d where signal='%s';",
				tablename2.c_str(), reply2.c_str(), data->type, GBKtoUTF8(data->group).c_str()
				, data->timelimit, data->timeperday, data->matchtype, signal2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg_2, NULL, NULL, &err_msg);
			delete[]temp_msg_2;
		}
		delete[]temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void myreply::get(std::string txt, replyinfo* reply, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[3000];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		sprintf(temp_msg, "select * from %s where signal='%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, myreply_callback, reply, &err_msg);
		sqlite3_close(olt_db);
	}
	void myreply::getallpartreply(std::map<const std::string, std::string>* b, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[3000];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		sprintf(temp_msg, "select * from %s where matchtype= 1", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, myreply_callback_partreply, b, &err_msg);
		sqlite3_close(olt_db);
	}
	void myreply::show(replyinfo* reply, int id, string title, char* position)

	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string title2 = GBKtoUTF8(title);
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		sprintf(temp_msg, "select * from %s where id=%d", title2.c_str(), id);
		rc = sqlite3_exec(olt_db, temp_msg, myreply_callback, reply, &err_msg);
		sqlite3_close(olt_db);
	}
	void myreply::getall(string title, char* position, Ui::Myreply* replyp)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		sprintf(temp_msg, "select * from %s", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, myreply_callbackall, replyp, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void banlist::create_table(sqlite3* olt_db, std::string tablename)
	{
		int rc = 0;
		char* err_msg = NULL;
		char sql[150];
		char temp_msg[150];
		sprintf(sql, "CREATE TABLE IF NOT EXISTS %s(CODE TEXT NOT NULL UNIQUE,QQ INTEGER NOT NULL,NOTE TEXT NOT NULL,IFERASE INTEGER NOT NULL);", tablename.c_str());
		rc = sqlite3_exec(olt_db, sql, NULL, NULL, &err_msg);
	}
	void banlist::insert(blackinfo* blackinfo, std::string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		char temp_msg[600];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string tablename2 = GBKtoUTF8(tablename);
		create_table(olt_db, tablename2);
		std::string code = GBKtoUTF8(blackinfo->code);
		std::string note = GBKtoUTF8(blackinfo->note);
		sprintf(temp_msg, "insert into %s(code,qq,note,iferase) values('%s',%lld,'%s',0);", tablename2.c_str(), code.c_str(), blackinfo->QQ, note.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void banlist::delcode(std::string code, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[1000];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string code2 = GBKtoUTF8(code);
		create_table(olt_db, title2);
		sprintf(temp_msg, "delete from %s where code ='%s'", title2.c_str(), code2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		std::string a = temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void banlist::delqq(long long qq, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[1000];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		create_table(olt_db, title2);
		sprintf(temp_msg, "delete from %s where qq = %lld", title2.c_str(), qq);
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		std::string a = temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void banlist::eraqq(long long qq, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[1000];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		create_table(olt_db, title2);
		sprintf(temp_msg, "UPDATE %s set iferase = 1 where qq = %lld;", title2.c_str(), qq);
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		std::string a = temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void banlist::getcode(std::string& note, std::string code, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string code2 = GBKtoUTF8(code);
		create_table(olt_db, title2);
		sprintf(temp_msg, "select * from %s where code ='%s'", title2.c_str(), code2.c_str());
		string testmsg = temp_msg;
		rc = sqlite3_exec(olt_db, temp_msg, banlist_callback, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		if (tem_string2.empty())* tem_string = "未查找到相关记录";
		sqlite3_close(olt_db);
		note = *tem_string;
		delete(tem_string);
	}
	void banlist::getcodeqq(std::string& qq, std::string code, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string code2 = GBKtoUTF8(code);
		create_table(olt_db, title2);
		sprintf(temp_msg, "select * from %s where code ='%s'", title2.c_str(), code2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, banlist_callbackqq, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		if (tem_string2.empty())* tem_string = "";
		sqlite3_close(olt_db);
		qq = *tem_string;
		delete(tem_string);
	}
	void banlist::getqq(std::string& info, long long qq, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string* tem_string = new string();
		if (tem_string == NULL || temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		create_table(olt_db, title2);
		sprintf(temp_msg, "select * from %s where qq= %lld", title2.c_str(), qq);
		rc = sqlite3_exec(olt_db, temp_msg, banlist_callback, tem_string, &err_msg);
		std::string tem_string2 = *tem_string;
		if (tem_string2.empty())* tem_string = "未查找到相关记录";
		sqlite3_close(olt_db);
		info = *tem_string;
		delete(tem_string);
	}
	void eventreply::create_table(string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		char* err_msg = NULL;
		char* sql = new char[300];
		char* temp_msg = new char[300];
		std::string title2 = GBKtoUTF8(tablename);
		sprintf(sql, "CREATE TABLE IF NOT EXISTS %s(event TEXT NOT NULL UNIQUE,process TEXT NOT NULL,delay INT NOT NULL);", title2.c_str());
		rc = sqlite3_exec(olt_db, sql, NULL, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
		delete[]sql;
		delete[]temp_msg;
	}
	void eventreply::insert(database::eventinfo* data, std::string tablename, char* position)

	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		char* err_msg1 = new char[300];
		std::string tablename2 = GBKtoUTF8(tablename);
		std::string event2 = GBKtoUTF8(data->eventname);
		std::string process2 = GBKtoUTF8(data->process);
		char* temp_msg = new char[3000];
		sprintf(temp_msg, "insert into %s(process,delay,event) values('%s',%d,'%s');",
			tablename2.c_str(), process2.c_str(), data->dealy, event2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
		if (rc == 19)
		{
			char* temp_msg_2 = new char[3000];
			sprintf(temp_msg_2, "UPDATE %s set process= '%s',delay= %d where event='%s';",
				tablename2.c_str(), process2.c_str(), data->dealy, event2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg_2, NULL, NULL, &err_msg);
			delete[]temp_msg_2;
		}
		delete[]temp_msg;
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void eventreply::del(std::string txt, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[100];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		sprintf(temp_msg, "delete from %s where event='%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, hiy_callback, NULL, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void eventreply::get(std::string txt, database::eventinfo* reply, string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[3000];
		char sql[150];
		if (temp_msg == NULL)
		{
			return;
		}
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		std::string txt2 = GBKtoUTF8(txt);
		sprintf(temp_msg, "select * from %s where event = '%s'", title2.c_str(), txt2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, eventreply_callback, reply, &err_msg);
		sqlite3_close(olt_db);
	}
	void eventreply::quickinsert(std::map<const std::string, database::eventinfo>* b, std::string tablename, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		int i;
		char* err_msg = NULL;
		char temp_msg[5000];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string tablename2 = GBKtoUTF8(tablename);
		create_table(tablename2, position);
		for (auto each : *b)
		{
			std::string tablename2 = GBKtoUTF8(tablename);
			std::string event2 = GBKtoUTF8(each.second.eventname);
			std::string process2 = GBKtoUTF8(each.second.process);
			char* temp_msg = new char[3000];
			sprintf(temp_msg, "insert into %s(process,delay,event) values('%s',%d,'%s');",
				tablename2.c_str(), process2.c_str(), each.second.dealy, event2.c_str());
			rc = sqlite3_exec(olt_db, temp_msg, NULL, NULL, &err_msg);
			if (rc == 19)
			{
				char* temp_msg_2 = new char[3000];
				sprintf(temp_msg_2, "UPDATE %s set process= '%s',delay= %d where event= '%s';",
					tablename2.c_str(), process2.c_str(), each.second.dealy, event2.c_str());
				rc = sqlite3_exec(olt_db, temp_msg_2, NULL, NULL, &err_msg);
				delete[]temp_msg_2;
			}
			delete[]temp_msg;
		}
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
	void eventreply::getall(std::map<const std::string, database::eventinfo>* b, std::string title, char* position)
	{
		sqlite3* olt_db = NULL;
		int rc = 0;
		char* err_msg = NULL;
		char temp_msg[300];
		char sql[150];
		std::string centre = GBKtoUTF8(position);
		rc = sqlite3_open(centre.c_str(), &olt_db);
		std::string title2 = GBKtoUTF8(title);
		create_table(title2, position);
		sprintf(temp_msg, "select * from %s", title2.c_str());
		rc = sqlite3_exec(olt_db, temp_msg, eventreply_callbackall, b, &err_msg);
		do
		{
			rc = sqlite3_close(olt_db);
			if (rc == SQLITE_BUSY)
			{
				Sleep(10);
				continue;
			}
			break;
		} while (1);
	}
}