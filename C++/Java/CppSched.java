import java.net.DatagramSocket;
import java.lang.String;
import java.util.Random;
import java.net.DatagramPacket;
import java.net.SocketAddress;

//import ByteUtils.*;

public class CppSched/* extends SchedPolicy*/
{
	DatagramSocket socket;
	SocketAddress cppAddr;
	public void Debug()
	{
		System.out.println("Java Aqui: ");
		Thread.dumpStack();
	}
	public CppSched()
	{
		try
		{
			Random randomGenerator= new Random();
			do
			{
				int portaEscolhida= randomGenerator.nextInt()%30000+31024;
				System.out.println("Porta escolhida: " + portaEscolhida);
				socket = new DatagramSocket(portaEscolhida);
				Debug();
			}
			while(GetPort()== -1);
			Debug();
			long key= randomGenerator.nextLong();
			System.out.println("Porta escolhida: " + GetPort());
			System.out.println("Número sorteado: " + key);
//			System
			Debug();
			Runtime r = Runtime.getRuntime();
			Process p = r.exec("./Escalonador.out "+ GetPort() + " " + key + " > /home/francisco/Escalonador.log 2>&1 &");//my_command > output.log 2>&1 &
			DatagramPacket pkt= new DatagramPacket(new byte[65000], 65000);
			Debug();
			long numReceived;
			do
			{
				Debug();
				socket.receive(pkt);
				Debug();
				numReceived= ByteUtils.bytesStringToLong(pkt.getData() );
				if(numReceived != key)
				{
					System.out.println("worng key. Expecting " + key + ",  got " + numReceived );
				}
			}
			while(numReceived != key);
			Debug();
			cppAddr = pkt.getSocketAddress();
			Debug();
			socket.send(new DatagramPacket(("Ack!").getBytes("US-ASCII"), 5, cppAddr));
			Debug();
		}
		catch (Throwable e)
		{
			System.out.println("exception happened - here's what I know: ");
			e.printStackTrace();
			System.exit(-1);
		}
	}
	public int GetPort()
	{
		return socket.getLocalPort();
	}
	public static void main(String[] args)
	{
		CppSched sched= new CppSched();
		System.out.println("Yeah!");
		
	}
}
