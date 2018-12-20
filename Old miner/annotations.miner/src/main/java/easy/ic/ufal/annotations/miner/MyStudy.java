package easy.ic.ufal.annotations.miner;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;

import org.apache.commons.io.FileUtils;
import org.repodriller.RepoDriller;
import org.repodriller.RepositoryMining;
import org.repodriller.Study;
import org.repodriller.filter.commit.OnlyInBranches;
import org.repodriller.filter.commit.OnlyModificationsWithFileTypes;
import org.repodriller.filter.range.Commits;
import org.repodriller.persistence.csv.CSVFile;
import org.repodriller.scm.GitRemoteRepository;

public class MyStudy implements Study {
	public static void main(String[] args) {
		org.apache.log4j.BasicConfigurator.configure();
		createDir("output", true);
		createDir("repos", false);
		new RepoDriller().start(new MyStudy());
	}

	public void execute() {
		try {
			new RepositoryMining()
			.in(GitRemoteRepository.hostedOn(FileUtils.readLines(new File("projectList.txt"), "utf-8"))
					.inTempDir("repos")
					.buildAsSCMRepositories())
			.through(Commits.all())
			.process(new MyCommitVisitor(), new CSVFile("output/report.csv"))
			.filters(
					new OnlyModificationsWithFileTypes(Arrays.asList(".java")),
					new OnlyInBranches(Arrays.asList("master"))
			)
			.mine();
		} catch (Exception e) {
			System.out.println("Error to mine");
		}
		
	}
	
	public static void createDir(String dirName, boolean deleteBefore) {
		File dir = new File(dirName);
		if (dir.exists()) {
			try {
				if (deleteBefore)
					FileUtils.deleteDirectory(dir);
				dir.mkdirs();
			} catch (IOException e) {
				System.out.println("error to delete dir " + dir.getName());
			}
		} else
			dir.mkdirs();
	}
}
