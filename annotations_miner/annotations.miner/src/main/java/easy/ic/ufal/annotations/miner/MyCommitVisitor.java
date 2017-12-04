package easy.ic.ufal.annotations.miner;

import org.repodriller.domain.Commit;
import org.repodriller.domain.Modification;
import org.repodriller.persistence.PersistenceMechanism;
import org.repodriller.scm.CommitVisitor;
import org.repodriller.scm.SCMRepository;

public class MyCommitVisitor implements CommitVisitor {

	public void process(SCMRepository repo, Commit commit, PersistenceMechanism writer) {
		for(Modification m : commit.getModifications()) {
			if (m.fileNameEndsWith(".java")) {
				writer.write(
						commit.getHash(),
						commit.getAuthor().getName(),
						commit.getCommitter().getName(),
						m.getFileName(),
						m.getType(),
						m.getDiff()
				);
			}
		}
	}
}
