IMAGES = \
	create.png linear.png spline.png \
	noise1.png noise2.png noise3.png perlin.png \
	greyscale.png compose.png apply.png \
	colormap.png convolve.png \
	op-add.png op-blend.png op-color.png op-darken.png \
	op-diff.png op-dissolve.png op-hue.png op-lighten.png \
	op-mult.png op-overlay.png op-sat.png op-screen.png \
	op-subtract.png op-value.png \
	clouds.png marble1.png marble2.png stars.png wood.png mandel.png \
        whirl-base.png whirl.png sine-base.png sine.png planet.png
MAINTAINERCLEANFILES = $(IMAGES)

docdir = $(sharedir)/doc/$(PACKAGE)
dist_doc_DATA = $(IMAGES) ptgen.html spline.gif

if HAVE_LIBPNG
create.png: $(srcdir)/../tests/test-create.pt
linear.png: $(top_srcdir)/tests/test-linear.pt 
spline.png: $(top_srcdir)/tests/test-spline.pt 
noise1.png: $(top_srcdir)/tests/test-noise1.pt 
noise2.png: $(top_srcdir)/tests/test-noise2.pt 
noise3.png: $(top_srcdir)/tests/test-noise3.pt 
perlin.png: $(top_srcdir)/tests/test-perlin.pt 
greyscale.png: $(top_srcdir)/tests/test-greyscale.pt 
compose.png: $(top_srcdir)/tests/test-compose.pt 
apply.png: $(top_srcdir)/tests/test-apply.pt 
colormap.png: $(top_srcdir)/tests/test-colormap.pt 
convolve.png: $(top_srcdir)/tests/test-convolve.pt 
op-add.png: $(top_srcdir)/tests/test-op-add.pt 
op-blend.png: $(top_srcdir)/tests/test-op-blend.pt 
op-color.png: $(top_srcdir)/tests/test-op-color.pt 
op-darken.png: $(top_srcdir)/tests/test-op-darken.pt 
op-diff.png: $(top_srcdir)/tests/test-op-diff.pt 
op-dissolve.png: $(top_srcdir)/tests/test-op-dissolve.pt 
op-hue.png: $(top_srcdir)/tests/test-op-hue.pt 
op-lighten.png: $(top_srcdir)/tests/test-op-lighten.pt 
op-mult.png: $(top_srcdir)/tests/test-op-mult.pt 
op-overlay.png: $(top_srcdir)/tests/test-op-overlay.pt 
op-sat.png: $(top_srcdir)/tests/test-op-sat.pt 
op-screen.png: $(top_srcdir)/tests/test-op-screen.pt 
op-subtract.png: $(top_srcdir)/tests/test-op-subtract.pt 
op-value.png: $(top_srcdir)/tests/test-op-value.pt 
clouds.png: $(top_srcdir)/tests/clouds.pt 
marble1.png: $(top_srcdir)/tests/marble1.pt 
marble2.png: $(top_srcdir)/tests/marble2.pt 
stars.png: $(top_srcdir)/tests/stars.pt 
wood.png: $(top_srcdir)/tests/wood.pt
mandel.png: $(top_srcdir)/tests/mandel.pt
whirl-base.png: $(top_srcdir)/tests/whirl-base.pt
whirl.png: $(top_srcdir)/tests/whirl.pt
sine-base.png: $(top_srcdir)/tests/sine-base.pt
sine.png: $(top_srcdir)/tests/sine.pt
planet.png: $(top_srcdir)/tests/planet.pt

$(IMAGES):
	$(top_builddir)/ptgen -o$@ -fpng --seed=17031980 --size=64 $^
endif

