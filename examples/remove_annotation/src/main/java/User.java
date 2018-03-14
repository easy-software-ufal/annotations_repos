

import javax.validation.constraints.NotNull;

public class User {
	
	@NotNull
	private String name;
	
	public String getName() {
		return this.name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
}
