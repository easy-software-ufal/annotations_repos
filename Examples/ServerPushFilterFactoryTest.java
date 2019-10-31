package io.dropwizard.jetty;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.google.common.collect.ImmutableList;
import com.google.common.io.Resources;
import io.dropwizard.configuration.YamlConfigurationFactory;
import io.dropwizard.jackson.Jackson;
import io.dropwizard.util.Duration;
import io.dropwizard.validation.BaseValidator;
import io.dropwizard.validation.MinDuration;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlets.PushCacheFilter;
import org.hamcrest.MatcherAssert;
import org.junit.Assert;
import org.junit.Test;
import org.mockito.Matchers;

import javax.annotation.Nullable;
import javax.servlet.DispatcherType;
import javax.validation.constraints.Null;
import java.io.File;
import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.EnumSet;
import java.util.concurrent.TimeUnit;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.fail;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;

public class ServerPushFilterFactoryTest {

    private Annotation minDuration;

    @Test
    public void testLoadConfiguration() throws Exception {
        final ServerPushFilterFactory serverPush = new YamlConfigurationFactory<>(
                ServerPushFilterFactory.class, BaseValidator.newValidator(),
                Jackson.newObjectMapper(), "dw-server-push")
                .build(new File(Resources.getResource("yaml/server-push.yml").toURI()));
        assertThat(serverPush.isEnabled()).isTrue();
        assertThat(serverPush.getAssociatePeriod()).isEqualTo(Duration.seconds(5));
        assertThat(serverPush.getMaxAssociations()).isEqualTo(8);
        assertThat(serverPush.getRefererHosts()).contains("dropwizard.io", "dropwizard.github.io");
        assertThat(serverPush.getRefererPorts()).contains(8444, 8445);
    }

    @Test
    public void testDefaultConfiguration() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        assertThat(serverPush.isEnabled()).isFalse();
        assertThat(serverPush.getAssociatePeriod()).isEqualTo(Duration.seconds(4));
        assertThat(serverPush.getMaxAssociations()).isEqualTo(16);
        assertThat(serverPush.getRefererHosts()).isNull();
        assertThat(serverPush.getRefererPorts()).isNull();
    }

    @Test
    public void testDontAddFilterByDefault() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();

        ServletContextHandler servletContextHandler = mock(ServletContextHandler.class);
        serverPush.addFilter(servletContextHandler);
        verify(servletContextHandler, never())
                .addFilter(PushCacheFilter.class, "/*", EnumSet.of(DispatcherType.REQUEST));
    }

    @Test
    public void testAddFilter() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        serverPush.setRefererHosts(ImmutableList.of("dropwizard.io", "dropwizard.github.io"));
        serverPush.setRefererPorts(ImmutableList.of(8444, 8445));
        serverPush.setEnabled(true);

        ServletContextHandler servletContextHandler = mock(ServletContextHandler.class);

        serverPush.addFilter(servletContextHandler);

        verify(servletContextHandler).setInitParameter("associatePeriod", "4000");
        verify(servletContextHandler).setInitParameter("maxAssociations", "16");
        verify(servletContextHandler).setInitParameter("hosts", "dropwizard.io,dropwizard.github.io");
        verify(servletContextHandler).setInitParameter("ports", "8444,8445");
        verify(servletContextHandler).addFilter(PushCacheFilter.class, "/*", EnumSet.of(DispatcherType.REQUEST));
    }

    @Test
    public void testRefererHostsAndPortsAreNotSet() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        serverPush.setEnabled(true);

        ServletContextHandler servletContextHandler = mock(ServletContextHandler.class);

        serverPush.addFilter(servletContextHandler);

        verify(servletContextHandler, never()).setInitParameter(eq("hosts"), anyString());
        verify(servletContextHandler, never()).setInitParameter(eq("ports"), anyString());
        verify(servletContextHandler).addFilter(PushCacheFilter.class, "/*", EnumSet.of(DispatcherType.REQUEST));
    }

    @Test
    public void testRefererHostIsCorrectlyAnnotated() {
        final Class<ServerPushFilterFactory> serverPushFilterFactoryClass = ServerPushFilterFactory.class;
        Field refererHostsField = null;
        try {
            refererHostsField = serverPushFilterFactoryClass.getDeclaredField("refererHosts");
        } catch (NoSuchFieldException e) {
            fail("refererHosts field not found.");
        }
        boolean containsNullableAnnotation = false;
        assert refererHostsField != null;
        Nullable nullable = refererHostsField.getAnnotation(Nullable.class);
        assertTrue(nullable != null);
    }

    @Test
    public void testAssociatePeriodIsCorrectlyAnnotated() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        Field associatePeriodField = null;
        try {
            associatePeriodField = serverPush.getClass().getDeclaredField("associatePeriod");
        } catch (NoSuchFieldException e) {
            fail("associatePeriod field not found.");
        }
        assert associatePeriodField != null;
        MinDuration minDuration = associatePeriodField.getAnnotation(MinDuration.class);
        assert minDuration != null;
        Assert.assertEquals(1, minDuration.value());
        Assert.assertEquals(1, minDuration.value());
        Assert.assertEquals(TimeUnit.MILLISECONDS, minDuration.unit());
        Assert.assertTrue(minDuration.inclusive());
    }

    @Test
    public void testSetRefererPortsIsCorrectlyAnnotated() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        Method setRefererPortsMethod = null;
        for (Method m : serverPush.getClass().getDeclaredMethods())
            if (m.getName().equals("setRefererPorts")) setRefererPortsMethod = m;
        assert setRefererPortsMethod != null;
        Annotation[] annotations = setRefererPortsMethod.getAnnotations();
        assertEquals(1, annotations.length);
        assertEquals(JsonProperty.class, annotations[0].annotationType());
    }

    @Test
    public void testIsEnabledIsCorrectlyAnnotated() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        Method isEnabled = null;
        for (Method m : serverPush.getClass().getDeclaredMethods())
            if (m.getName().equals("isEnabled")) isEnabled = m;
        assert isEnabled != null;
        Annotation[] annotations = isEnabled.getAnnotations();
        assertEquals(1, annotations.length);
        assertEquals(JsonProperty.class, annotations[0].annotationType());
    }

    @Test
    public void testGetRefererPortsIsCorrectlyAnnotated() {
        final ServerPushFilterFactory serverPush = new ServerPushFilterFactory();
        Method getRefererPortsMethod = null;
        try {
            getRefererPortsMethod = serverPush.getClass().getDeclaredMethod("getRefererPorts");
        } catch (NoSuchMethodException e) {
            fail("getRefererPorts field not found.");
        }
        assert getRefererPortsMethod != null;
        Annotation[] annotations = getRefererPortsMethod.getAnnotations();
        assertEquals(2, annotations.length);
        assertEquals(JsonProperty.class, annotations[0].annotationType());
        assertEquals(Nullable.class, annotations[1].annotationType());
    }

}
