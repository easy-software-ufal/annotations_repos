package easy.ic.ufal.annotations.miner;

import java.io.File;
import java.util.List;
import java.util.regex.Pattern;

import org.apache.commons.io.FileUtils;
import org.repodriller.domain.Commit;
import org.repodriller.domain.DiffBlock;
import org.repodriller.domain.DiffParser;
import org.repodriller.domain.Modification;
import org.repodriller.persistence.PersistenceMechanism;
import org.repodriller.scm.CommitVisitor;
import org.repodriller.scm.SCMRepository;

public class MyCommitVisitor implements CommitVisitor {
	private Pattern patternOk = Pattern.compile("\\s@[a-zA-Z]+");
	private Pattern patternNotOk = Pattern.compile("(\\/\\/|\\*)[^@]*@[a-zA-Z]+");

	public void process(SCMRepository repo, Commit commit, PersistenceMechanism writer) {
		DiffParser diffParser = null;

		File folder = new File("output" + File.separator + this.getProjectName(repo));
		this.createFolder(folder);

		for (Modification m : commit.getModifications()) {
			if (m.fileNameEndsWith(".java")) {
				boolean detectedLines = false;

				diffParser = new DiffParser(m.getDiff());

				try {
					ReportWriter reportWriter = new ReportWriter(
							new File(folder.getAbsolutePath() + File.separator + commit.getHash() + File.separator
									+ m.getFileName().substring(0, m.getFileName().lastIndexOf("."))));

					for (DiffBlock diffBlock : diffParser.getBlocks()) {
						for (String line : diffBlock.getLines()) {
							if (this.checkLine(line) && this.hasAnnotation(line)) {
								if (detectedLines == false) {
									this.createFolder(
											new File(folder.getAbsolutePath() + File.separator + commit.getHash()));

									reportWriter.writeLine("BasicInfo:" + System.lineSeparator());
									reportWriter.writeLine("commit: " + commit.getHash());
									reportWriter.writeLine("file: " + m.getFileName());
									reportWriter.writeLine("================================================"
											+ System.lineSeparator());

									reportWriter.writeLine("Detected Lines:" + System.lineSeparator());
									detectedLines = true;
								}
								reportWriter.writeLine(line);
							}
						}
					}

					if (detectedLines) {
						reportWriter
								.writeLine("================================================" + System.lineSeparator());
						reportWriter.writeLine("Diff Block:" + System.lineSeparator());
						reportWriter.writeLine(diffParser.getFullDiff());
					}

					reportWriter.close();
				} catch (Exception e) {
					System.out.println("error to write report");
				}
			}
		}
	}

	private boolean hasAnnotation(String line) {
		if (this.containsProhibitedWords(line))
			return false;
		return !this.patternNotOk.matcher(line).find() && this.patternOk.matcher(line).find();
	}

	private boolean containsProhibitedWords(String line) {
		try {
			List<String> prohibitedWords = FileUtils.readLines(new File("prohibited_annotations.txt"), "utf-8");
			for (String word : prohibitedWords)
				if (line.contains(word))
					return true;
		} catch (Exception e) {
			return false;
		}

		return false;
	}

	private boolean checkLine(String line) {
		if (line.startsWith("@@ ") || (!line.startsWith("+") && !line.startsWith("-")))
			return false;
		return true;
	}

	private String getProjectName(SCMRepository repo) {
		String uri = repo.getOrigin();
		if (uri.endsWith("/"))
			uri = uri.substring(0, uri.length() - 1);
		return uri.substring(uri.lastIndexOf("/") + 1);
	}

	private void createFolder(File folder) {
		if (!folder.exists())
			folder.mkdirs();
	}
}
