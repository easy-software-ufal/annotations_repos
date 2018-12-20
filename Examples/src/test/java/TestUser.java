

import static org.junit.Assert.*;

import java.util.Set;

import javax.validation.ConstraintViolation;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;

import org.junit.Test;

public class TestUser {

	@Test
	public void testAll() {
		ValidatorFactory factory = Validation.buildDefaultValidatorFactory();
		Validator validator = factory.getValidator();

		User user = new User();
		user.setName("Carlos");

		Set<ConstraintViolation<User>> violations = validator.validate(user);
		assertTrue(violations.isEmpty());
	}
	
	@Test
	public void testNullAttr() throws Exception {
		ValidatorFactory factory = Validation.buildDefaultValidatorFactory();
		Validator validator = factory.getValidator();

		User user = new User();

		Set<ConstraintViolation<User>> violations = validator.validate(user);
		assertFalse(violations.isEmpty());
	}
}
