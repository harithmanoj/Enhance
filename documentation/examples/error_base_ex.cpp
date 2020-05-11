#include <error_base.enh.h>
#include <iostream>

class derived_type : public enh::error_base<unsigned char>
{
public:
	static constexpr error USER_DEF = 0x04;

#ifdef ERROR_BASE_LOG
private:
	virtual std::string derived_class() const noexcept
	{
		return "derived_type";
	}

	virtual std::string error_string()  const
	{
		std::string ret = error_base::error_string();
		if (ret == "SAFE")
			return ret;
		
		if (checkFlag(USER_DEF))
			ret += " + USER_DEF";
		return ret;
	}
#endif
public:
	void setFlag__(error fl)
	{
		setFlag(fl);
	}
};

int main()
{
	LOG_LINE;

	derived_type t;

	t.setFlag__(derived_type::INVALID_ARG);

	std::cout << std::boolalpha << t.checkFlag(derived_type::INVALID_ARG);

	ERROR_FLAG_LOG(t);

	t.setFlag__(derived_type::USER_DEF);

	std::cout << std::boolalpha << t.checkFlag(derived_type::USER_DEF);

	ERROR_FLAG_LOG(t);
	return 0;
}


/* ****************************************************************************

Output :

Log file will not be made if _DEBUG is not set or ENH_CLEAR_OP__ is set or if 
optimisation is more than 1

Console:
truetrue

14720_thread_fn_main.log:

Thread id : 14720
thread first logging function main
				F:\error_base_ex.cpp :     36              main
				F:\error_base_ex.cpp :     44              main ::   derived_type t flag :  + INVALID_ARG
				F:\error_base_ex.cpp :     50              main ::   derived_type t flag :  + INVALID_ARG + USER_DEF




******************************************************************************/