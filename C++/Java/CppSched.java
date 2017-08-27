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
	public CppSched()
	{
		try
		{
			socket = new DatagramSocket();
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
			Random randomGenerator= new Random();
			long key= randomGenerator.nextLong();
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
			Runtime r = Runtime.getRuntime();
			Process p = r.exec("./Escalonador "+ GetPort() + " " + key + " &");//my_command > output.log 2>&1 &
			DatagramPacket pkt= new DatagramPacket(new byte[65000], 65000);
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
			long numReceived;
			do
			{
				System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
				socket.receive(pkt);
				System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
				numReceived= ByteUtils.bytesToLong(pkt.getData() );
				if(numReceived != key)
				{
					System.out.println("worng key. Expecting " + key + ",  got " + numReceived );
				}
			}
			while(numReceived != key);
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
			cppAddr = pkt.getSocketAddress();
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
			socket.send(new DatagramPacket(("Ack!").getBytes("US-ASCII"), 5, cppAddr));
			System.out.println("Java Aqui: " + Thread.currentThread().getStackTrace()[0].getLineNumber());
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
		return socket.getPort();
	}
	public static void main(String []args)
	{
		CppSched sched= new CppSched();
		System.out.println("Yeah!");
		
	}
}
