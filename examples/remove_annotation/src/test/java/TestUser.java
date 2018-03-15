

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Set;

import javax.validation.ConstraintViolation;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;

import org.junit.BeforeClass;
import org.junit.Test;

public class TestUser {
	
	private static Validator validator = null;
	
	@BeforeClass
	public static void initValidator() {
		ValidatorFactory factory = Validation.buildDefaultValidatorFactory();
		validator = factory.getValidator();
	}

	@Test
	public void checkUserValidity() {
		User user = new User();
		user.setName("Carlos");

		Set<ConstraintViolation<User>> violations = validator.validate(user);
		assertTrue(violations.isEmpty());
	}
	
	@Test
	public void testNullAttr() throws Exception {
		User user = new User();

		Set<ConstraintViolation<User>> violations = validator.validate(user);
		assertFalse(violations.isEmpty());
	}
}
