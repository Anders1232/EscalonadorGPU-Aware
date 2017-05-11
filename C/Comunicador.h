struct communicator
{
	unsigned int type;
	void* instance;
};
typedef struct communicator Communicator;

void SendMessage(Communicator *comm, void* message, unsigned messageSize);
