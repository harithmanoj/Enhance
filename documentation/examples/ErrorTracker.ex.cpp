#include <ErrorTracker.enh.h>
#include <iostream>

class derived_type : public enh::ErrorTracker<unsigned char>
{
public:
	static constexpr UnderlyingErrorType USER_DEF = 0x04;

#ifdef ERROR_BASE_LOG
private:
	virtual std::string derivedClassName() const noexcept
	{
		return "derived_type";
	}
#endif
public:
	virtual std::string errorToString()  const
	{
		std::string ret = ErrorTracker::errorToString();
		if (ret == "SAFE")
			return ret;
		
		if (checkErrorFlag(USER_DEF))
			ret += " + USER_DEF";
		return ret;
	}
};

int main()
{
	LOG_LINE_I;

	derived_type t;

	t.setErrorFlag(derived_type::INVALID_ARG);

	std::cout << std::boolalpha << t.checkErrorFlag(derived_type::INVALID_ARG);

	FLAG_LOG_E(t);

	t.setErrorFlag(derived_type::USER_DEF);

	std::cout << std::boolalpha << t.checkErrorFlag(derived_type::USER_DEF);

	FLAG_LOG_E(t);
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