package easy.ic.ufal.annotations.miner;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

public class ReportWriter {
	
	private BufferedWriter bufferedWriter = null;
	private File file = null;
	
	public ReportWriter(File file) throws Exception {
		this.file = file;
	}
	
	public void writeLine(String line) throws Exception {
		if (this.bufferedWriter == null)
			this.bufferedWriter = new BufferedWriter(new FileWriter(this.file));
		
		this.bufferedWriter.write(line + System.lineSeparator());
	}
	
	public void close() throws Exception {
		if (this.bufferedWriter != null)
			this.bufferedWriter.close();
	}
}
