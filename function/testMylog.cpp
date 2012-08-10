#include "myLog.h"

int main ()
{
	const int count = 3;
	Log(logDEBUG) << "A loop with " << count << " iterations" <<std::endl;
	for (int i = 0; i != count; ++i)
	{
		Log(logDEBUG) << "the counter i = " << i;
	}
	return 0;
}