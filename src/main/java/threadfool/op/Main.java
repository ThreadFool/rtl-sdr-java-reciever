package threadfool.op;

import java.io.FileOutputStream;

public class Main
{
	public static void main(String[] args) throws Exception
	{
		RtlSdr rtlSdr = new RtlSdr();

		if(rtlSdr.open() !=0){
			throw new RuntimeException("Rtl sdr opening failed");
		}

		rtlSdr.setSampleRate(2_000_000); //2ms/s
		rtlSdr.setCenterFreq(1_090_000_000L); // 1090 MHz (ADS-B)


		byte[] buffer = new byte[16384];

		try(FileOutputStream fos = new FileOutputStream("iq.raw")){
			for(int i = 0; i < 100; i++){
				int n = rtlSdr.readSync(buffer);
				if(n > 0){
					fos.write(buffer,0,n);
					System.out.println("Read " + n + " bytes");
				}
			}
		}

		rtlSdr.close();
		System.out.println("Done");
	}
}