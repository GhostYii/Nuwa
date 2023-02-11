#include "UUID.h"
#include <random>

static std::random_device randomDevice;
static std::mt19937_64 engine(randomDevice());
static std::uniform_int_distribution<uint64_t> uniformDistribution;

Nuwa::UUID::UUID()
	: uuid(uniformDistribution(engine))
{

}

Nuwa::UUID::UUID(uint64_t uuid)
	: uuid(uuid)
{
}
