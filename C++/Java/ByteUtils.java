import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
//package ByteUtils;

public class ByteUtils
{
	private static ByteBuffer buffer = ByteBuffer.allocate(Long.BYTES);
	public static byte[] longToBytes(long x)
	{
		buffer.putLong(0, x);
		return buffer.array();
	}
	public static long bytesStringToLong(byte[] bytes)
	{
//		buffer.put(bytes, 0, bytes.length);
//		buffer.flip();//need flip 
		System.out.println("String gerada dos bytes: " + new String(bytes, StandardCharsets.US_ASCII));
		return Long.parseLong(new String(bytes, StandardCharsets.US_ASCII), 10);
//		return buffer.getLong();
	}
}
