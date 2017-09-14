import java.net.DatagramSocket;
import java.lang.String;
import java.util.Random;
import java.net.DatagramPacket;
import java.net.SocketAddress;
import java.nio.charset.StandardCharsets;

//import ByteUtils.*;

public class CppSched/* extends SchedPolicy*/
{
	DatagramSocket socket;
	SocketAddress cppAddr;
	boolean debug=false;
	protected abstract String GetSchedPolicy();
	public void Debug()
	{
		if(debug)
		{
			System.out.println("Java Aqui: ");
			Thread.dumpStack();
		}
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
					System.out.println("wrong key. Expecting " + key + ",  got " + numReceived );
				}
			}
			while(numReceived != key);
			Debug();
			cppAddr = pkt.getSocketAddress();
			Debug();
			socket.send(new DatagramPacket(("Ack!").getBytes("US-ASCII"), ("Ack!").getBytes("US-ASCII").length, cppAddr));
			Debug();
			
			//enviar escalonador desejado
			String schedType= GetSchedPolicy();
			socket.send(new DatagramPacket((schedType).getBytes("US-ASCII"), schedType.getBytes("US-ASCII").length, cppAddr));
			if(Receive("[SchedTypeAwnser]").contains("Fail"))
			{
				Debug();
				throw(new String(Deu ruim));
			}
			System.out.println("Escalonador gerado!");
			
			
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
	protected String Receive(String begin)
	{
		DatagramPacket pkt= new DatagramPacket(new byte[65000], 65000);
		String received;
		do
		{
			Debug();
			socket.receive(pkt);
			received= pkt.getData().toString().trim();
			if(!received.startsWith(begin))
			{
				System.out.println("wrong key. Expecting " + begin + ",  got " + pkt.getData().toString() );
			}
		}
		while(!received.startsWith(begin));
		return received;
	}
}
