#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <set>
#include <ui_myreply.h>
#include <map>
namespace database
{
	struct replyinfo
	{
		std::string signal;
		std::string replymsg;
		int type = 0;
		std::string group;
		int timelimit=0;
		int timeperday=0;
		int matchtype=0;
	};
	struct blackinfo
	{
		std::string code;
		long long QQ = 0;
		std::string note;
	};
	struct eventinfo
	{
		std::string process;
		int dealy = 0;
		std::string eventname;
	};
	int hiy_callback(void* tem_string, int argc, char* value[], char* name[]);
	int list_callback(void* tem_string, int argc, char* value[], char* name[]);
	int myreply_callback(void* tem_string, int argc, char* value[], char* name[]);
	int myreply_callbackall(void* tem_reply, int argc, char* value[], char* name[]);
	int myreply_callback_recorder(void* tem_reply, int argc, char* value[], char* name[]);
	int banlist_callback(void* tem_string, int argc, char* value[], char* name[]);
	int banlist_callbackqq(void* tem_string, int argc, char* value[], char* name[]);
	class hiy
	{
	public:
		void insert(std::string a, std::string b, std::string tablename, char* position);
		void quickinsert(std::map<const std::string, std::string>* b, std::string tablename, char* position);
		void get(std::string txt, std::string& reply, std::string title, char* position, bool type = false);
		void del(std::string txt, std::string  title, char* position);
		void era(std::string txt, char* position);
		void getall(std::map<const std::string, std::string>* b, std::string title, char* position);
		void getallFQT(std::string title, char* position, Ui::Myreply* replyp);
		void list(std::string& reply, char* position);
		void index(std::string& index, std::string  title, int page, char* position);
	private:
		void create_table(sqlite3* olt_db, std::string tablename);
	};
	class myreply
	{
	public:
		void insert(database::replyinfo* b, std::string tablename, char* position);
		void get(std::string txt, replyinfo* reply, std::string title, char* position);
		void del(std::string txt, std::string title, char* position);
		void era(std::string title, char* position);
		void show(replyinfo* reply,int id, std::string title, char* position);
		void getall(std::string title, char* position, Ui::Myreply* replyp);
		void get_record(std::string txt, std::pair<long long, int>* reply, char* position);
		void update_record(std::string signal, std::pair<long long, int>* reply,  char* position);
		void create_table(std::string tablename,char* position);
		void create_table_record( char* position);
		void getallpartreply(std::map<const std::string, std::string>* b, std::string title, char* position);
	private:
	};
	class eventreply
	{
	public:
		void insert(database::eventinfo* b, std::string tablename, char* position);
		void get(std::string txt, eventinfo* reply, std::string title, char* position);
		void del(std::string txt, std::string title, char* position);
		void create_table(std::string tablename, char* position);
		void quickinsert(std::map<const std::string, database::eventinfo>* b, std::string tablename, char* position);
		void getall(std::map<const std::string, database::eventinfo>* b, std::string title, char* position);
	private:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	};
	class banlist
	{
	public:
		void insert(blackinfo* blackinfo, std::string tablename, char* position);
		void getcode(std::string& note, std::string code, std::string title, char* position);
		void getcodeqq(std::string& qq, std::string code, std::string title, char* position);
		void getqq(std::string& info, long long qq, std::string title, char* position);
		void delcode(std::string code, std::string title, char* position);
		void delqq(long long qq, std::string title, char* position);
		void eraqq(long long qq, std::string title, char* position);
	private:
		void create_table(sqlite3* olt_db, std::string tablename);
	};
}
