package threadfool.op;

public class RtlSdr
{
	static
	{
		System.loadLibrary("rtlsdr_jni");
	}

	public native int open();

	public native int setCenterFreq(long hz);

	public native int setSampleRate(int hz);

	public native int readSync(byte[] buffer);

	public native void close();
}
