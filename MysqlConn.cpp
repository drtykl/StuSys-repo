#include "MysqlConn.h"

MysqlConn::MysqlConn()
{
	m_con = mysql_init(nullptr);
	mysql_set_character_set(m_con, "GBK");
}

MysqlConn::~MysqlConn()
{
	if (m_con != nullptr) {
		mysql_close(m_con);
	}
	free_result();
}

bool MysqlConn::connect(string host, string user, string pwd, string db_name, int port)
{
	MYSQL* ptr = mysql_real_connect(m_con, host.c_str(), user.c_str(), pwd.c_str(), db_name.c_str(), port, nullptr, 0);
	return ptr != nullptr;
}

bool MysqlConn::update(string sql)
{
	if (!mysql_query(m_con, sql.c_str()))return true;
	return false;
}

bool MysqlConn::query(string sql)
{
	free_result();
	now_count = 0;
	if (!mysql_query(m_con, sql.c_str())) {
		m_result = mysql_store_result(m_con);
		now_count = mysql_num_fields(m_result);
		return true;
	}
	return false;
}

bool MysqlConn::next()
{
	if (m_result != nullptr) {
		m_row = mysql_fetch_row(m_result);
		return m_row != nullptr;
	}
	return false;
}

string MysqlConn::value(int index)
{
	if (m_row != nullptr) {
		if (index >= 0 && index < now_count) {
			char* val = m_row[index];
			unsigned long length = mysql_fetch_lengths(m_result)[index];
			return string(val,length);
		}
	}
	return string();
}

bool MysqlConn::transaction()
{
	return mysql_autocommit(m_con, false);
}

bool MysqlConn::commit()
{
	return mysql_commit(m_con);
}

bool MysqlConn::rollback()
{
	return mysql_rollback(m_con);
}

int MysqlConn::col_count()
{
	return now_count;
}

void MysqlConn::free_result()
{
	if (m_result != nullptr) {
		mysql_free_result(m_result);
		m_result = nullptr;
	}
}
