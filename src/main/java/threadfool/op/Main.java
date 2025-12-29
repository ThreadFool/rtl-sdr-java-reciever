package threadfool.op;

public class Main
{

	static {
		System.loadLibrary("rtlsdr_jni");
	}

	public static void main(String[] args)
	{
		System.out.println("JNI works");
	}
}