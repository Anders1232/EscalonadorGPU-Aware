#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

template <class T>
class Serializable
{
	public:
		virtual static char* Serialize(T& instance)=0;
		virtual static T Deserialize(char* data)=0;
}

#endif // SERIALIZABLE_H
