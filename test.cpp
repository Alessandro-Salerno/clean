#include "object.h"
#include "io.h"
#include "types.h"

int main()
{
	{
		using namespace clean;
		var x = Object(1);
		x.add(Object(10));
		io::println(integer::tostring(x.cast<int>()));
	}

	return 0;
}
