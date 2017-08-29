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
			boolean mostrarBruxariaDoJava= false;
			do
			{
				Debug();
				socket.receive(pkt);
				Debug();
				if(mostrarBruxariaDoJava)
				{
					System.out.println(new String(pkt.getData(), StandardCharsets.US_ASCII) + "= rede");
					System.out.println(String.valueOf(key) + "= gerado");
					System.out.println(new String(pkt.getData(), StandardCharsets.US_ASCII).getBytes() + "= rede");
					System.out.println(String.valueOf(key).getBytes() + "= gerado");
					System.out.println(new String(pkt.getData(), StandardCharsets.US_ASCII).getBytes(StandardCharsets.US_ASCII) + "= rede ASCII");
					System.out.println(String.valueOf(key).getBytes(StandardCharsets.US_ASCII) + "= gerado ASCII");
					System.out.println(new String(pkt.getData(), StandardCharsets.US_ASCII).getBytes(StandardCharsets.US_ASCII) + "= rede ASCII -> ASCII");
					System.out.println(String.valueOf(key).getBytes(StandardCharsets.US_ASCII) + "= gerado ASCII -> ASCII");
					System.out.println(new String(pkt.getData(), StandardCharsets.US_ASCII).toCharArray() + "= rede char array");
					System.out.println(String.valueOf(key).toCharArray() + "= gerado char array");
	
					
					String receivedString= new String(pkt.getData(), StandardCharsets.US_ASCII);
					String originalString= String.valueOf(key);
					System.out.println("tamanho original: " + originalString.length());
					System.out.println("tamanho recebido: " + receivedString.length());
					for(int count=0; count < originalString.length(); count++)
					{
						System.out.println("[" + count + "]" + originalString.charAt(count) + " : original");
						System.out.println("[" + count + "]" + receivedString.charAt(count) + " : recebido");
						
					}
					
					if( (new String(pkt.getData(), StandardCharsets.US_ASCII) ).equals(String.valueOf(key)) )
					{
						System.out.println("Aha!");
					}
				}
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
			socket.send(new DatagramPacket(("Ack!").getBytes("US-ASCII"), ("Ack!").getBytes("US-ASCII").length, cppAddr));
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
