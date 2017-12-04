package easy.ic.ufal.annotations.miner;

import java.util.Arrays;

import org.repodriller.RepoDriller;
import org.repodriller.RepositoryMining;
import org.repodriller.Study;
import org.repodriller.filter.commit.OnlyInBranches;
import org.repodriller.filter.commit.OnlyModificationsWithFileTypes;
import org.repodriller.filter.range.Commits;
import org.repodriller.persistence.csv.CSVFile;
import org.repodriller.scm.GitRepository;

public class MyStudy implements Study {
	public static void main(String[] args) {
		org.apache.log4j.BasicConfigurator.configure();
		// TODO: create output folder
		new RepoDriller().start(new MyStudy());
	}

	public void execute() {
		new RepositoryMining()
			.in(GitRepository.singleProject("repos/repodriller"))
			.through(Commits.all())
			.process(new MyCommitVisitor(), new CSVFile("output/report.csv"))
			.filters(
					new OnlyModificationsWithFileTypes(Arrays.asList(".java")),
					new OnlyInBranches(Arrays.asList("master"))
			)
			.mine();
	}
}
