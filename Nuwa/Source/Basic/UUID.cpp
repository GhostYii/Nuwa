#include "UUID.h"
#include <random>

static std::random_device randomDevice;
static std::mt19937_64 engine(randomDevice());
static std::uniform_int_distribution<Nuwa::uint64> uniformDistribution;

Nuwa::UUID::UUID()
	: uuid(uniformDistribution(engine))
{

}

Nuwa::UUID::UUID(Nuwa::uint64 uuid)
	: uuid(uuid)
{
}

Nuwa::uint64 Nuwa::UUID::Generate()
{
	return uniformDistribution(engine);
}
