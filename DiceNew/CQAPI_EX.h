#pragma once

#include <string>
#include <map>
#include <vector>

#include "cqdefine.h"
class Unpack;

namespace cq::api
{
	//����������־ 
	int addLog(int Priorty, const char* Type, const char* Content);

	//���ͺ�����Ϣ
	//Auth=106 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID 
	int send_private_msg(long long QQ, const char* msg);
	//���ͺ�����Ϣ
	//Auth=106 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID 
	int send_private_msg(long long QQ, const std::string& msg);

	//����Ⱥ��Ϣ 
	//Auth=101 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int send_group_msg(long long GroupID, const char* msg);
	//����Ⱥ��Ϣ 
	//Auth=101 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int send_group_msg(long long GroupID, const std::string& msg);


	//������������Ϣ 
	//Auth=103 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int send_discuss_msg(long long DiscussID, const char* msg);
	//������������Ϣ 
	//Auth=103 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int send_discuss_msg(long long DiscussID, const std::string& msg);

	//������ Auth=110
	int sendLike(long long QQID, int times);

	//ȡCookies (���ã��˽ӿ���Ҫ�ϸ���Ȩ) 
	//Auth=20
	const char* getCookies();

	//�������� 
	const char* getRecord(
		const char* file, // �յ���Ϣ�е������ļ��� (file) 
		const char* outformat // Ӧ������ĸ�ʽ mp3,amr,wma,m4a,spx,ogg,wav,flac
	);
	//�������� 
	std::string getRecord(
		const std::string& file, // �յ���Ϣ�е������ļ��� (file) 
		const std::string& outformat // Ӧ������ĸ�ʽ mp3,amr,wma,m4a,spx,ogg,wav,flac
	);

	//ȡCsrfToken (���ã��˽ӿ���Ҫ�ϸ���Ȩ) 
	//Auth=20 ��QQ��ҳ�õ���bkn/g_tk��
	int getCsrfToken();

	//ȡӦ��Ŀ¼ 
	//���ص�·��ĩβ��"\" 
	const char* get_app_directory();

	//ȡ��¼QQ 
	long long get_login_user_id();

	//ȡ��¼�ǳ� 
	const char* getLoginNick();

	//��ȺԱ�Ƴ� Auth=120 
	int set_group_kick(
		long long GroupID, long long QQID,
		CQBOOL RefuseForever = false // ���Ϊ�棬�򡰲��ٽ��մ��˼�Ⱥ���롱�������� 
	);

	//��ȺԱ���� Auth=121 
	int set_group_ban(
		long long GroupID, long long QQID,
		long long Time = 60 // ���Ե�ʱ�䣬��λΪ�롣���Ҫ�����������д0 
	);

	//��Ⱥ����Ա Auth=122 
	int set_group_admin(
		long long GroupID, long long QQID,
		CQBOOL isAdmin = true // ��/���ù���Ա ��/ȡ������Ա 
	);

	//��Ⱥ��Աר��ͷ�� Auth=128 ��Ⱥ��Ȩ�� 
	int set_group_special_title(
		long long GroupID, long long QQID,
		const char* Title, // ���Ҫɾ����������� 
		long long ExpireTime = -1 // ר��ͷ����Ч�ڣ���λΪ�롣���������Ч��������д-1
	);
	//��Ⱥ��Աר��ͷ�� Auth=128 ��Ⱥ��Ȩ�� 
	int set_group_special_title(
		long long GroupID, long long QQID,
		const std::string& Title, // ���Ҫɾ����������� 
		long long ExpireTime = -1 // ר��ͷ����Ч�ڣ���λΪ�롣���������Ч��������д-1
	);

	//��ȫȺ���� Auth=123 
	int setGroupWholeBan(
		long long GroupID,
		CQBOOL isBan = true // ��/���� ��/�ر� 
	);

	//������ȺԱ���� Auth=124 
	int setGroupAnonymousBan(
		long long GroupID,
		const char* AnonymousToken, // Ⱥ��Ϣ�¼��յ��ġ����������� 
		long long banTime = 60 // ���Ե�ʱ�䣬��λΪ�롣��֧�ֽ�� 
	);

	//��Ⱥ�������� Auth=125 
	int setGroupAnonymous(long long GroupID, CQBOOL enableAnonymous = true);

	//��Ⱥ��Ա��Ƭ Auth=126 
	int setGroupCard(long long GroupID, long long QQID, const char* newGroupNick);

	//��Ⱥ��Ա��Ƭ Auth=126 
	int setGroupCard(long long GroupID, long long QQID, const std::string& newGroupNick);

	//��Ⱥ�˳� Auth=127 ����,�˽ӿ���Ҫ�ϸ���Ȩ 
	int set_group_leave(
		long long GroupID,
		CQBOOL isDismiss = false // ��/��ɢ��Ⱥ (Ⱥ��) ��/�˳���Ⱥ (����Ⱥ��Ա) 
	);

	//���������˳� Auth=140 
	int set_discuss_leave(
		long long DiscussID
	);

	//�ú���������� Auth=150 
	int set_friend_add_request(
		const char* RequestToken, // �����¼��յ��ġ�������ʶ������ 
		int ReturnType, // #����_ͨ�� �� #����_�ܾ� 
		const char* Remarks // ��Ӻ�ĺ��ѱ�ע 
	);

	//��Ⱥ������� Auth=151 
	int set_group_add_request(
		const char* RequestToken, // �����¼��յ��ġ�������ʶ������ 
		int RequestType, // ���������¼������������� #����_Ⱥ��� �� #����_Ⱥ���� 
		int ReturnType, // #����_ͨ�� �� #����_�ܾ� 
		const char* Reason // �������ɣ��� #����_Ⱥ��� �� #����_�ܾ� ʱ����
	);

	//������������ʾ,��ʱ��֪����ʲô�õ�
	int setFatal(const char* ErrorMsg);


	class GroupMemberInfo;
	//ȡȺ��Ա��Ϣ (֧�ֻ���) Auth=130 
	GroupMemberInfo get_group_member_info(long long GroupID, long long QQID, CQBOOL DisableCache = false);

	class StrangerInfo;
	//ȡİ������Ϣ (֧�ֻ���) Auth=131 
	StrangerInfo get_stranger_info(long long QQID, CQBOOL DisableCache = false);

	//ȡȺ��Ա�б� Auth=160  
	std::vector<GroupMemberInfo> get_group_member_list(long long GroupID);

	//ȡȺ�б� Auth=161  
	std::map<long long, std::string> get_group_list();


	//������Ϣ Auth=180
	int deleteMsg(long long MsgId);

	const char* getlasterrmsg();

	// Ⱥ��Ա��Ϣ
	class GroupMemberInfo final
	{
		void setdata(Unpack& u);
	public:
		long long group_id{};
		long long user_id{};
		std::string nickname{};
		std::string GroupNick{};
		int Gender{}; // 0/���� 1/Ů��
		int Age{};
		std::string Region{};
		int AddGroupTime{};
		int LastMsgTime{};
		std::string LevelName{};
		int role{}; //1/��Ա 2/����Ա 3/Ⱥ��
		std::string Title{};
		int ExpireTime{}; // -1 ��������
		CQBOOL NaughtyRecord{};
		CQBOOL canEditGroupNick{};

		explicit GroupMemberInfo(Unpack& msg);
		explicit GroupMemberInfo(const char* msg); //��API����
		explicit GroupMemberInfo(std::vector<unsigned char> data); //��Unpack����
		GroupMemberInfo() = default;

		std::string tostring() const;
	};

	// İ������Ϣ
	class StrangerInfo final
	{
	public:
		long long user_id = 0;
		std::string nickname = ""; //�ǳ�
		int sex = 255; //0/���� 1/Ů�� 255/δ֪
		int age = -1; //����

		explicit StrangerInfo(const char* msg);
		StrangerInfo() = default;

		std::string tostring() const;
	};
}
