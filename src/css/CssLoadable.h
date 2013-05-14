#ifndef CSSLOADABLE_H
#define CSSLOADABLE_H

#include "core/BoxModel.h"
#include "libcss/libcss.h"
#include "debug/Print.h"

namespace ofx {

namespace boxModel {

namespace css {

static void* cssReallocate(void *ptr, size_t size, void *pw) {
	return realloc(ptr, size);
}

static css_error cssResolveUrl(void *pw, const char *base, lwc_string *rel, lwc_string **abs){

}

template <class BoxModelType>
class CssLoadable {
public:
	CssLoadable() {};
	~CssLoadable() {};

	void loadCss(std::string path) {
		ofBuffer buffer = ofBufferFromFile(path);
		setCss(buffer.getText());
	}

	void setCss(std::string cssDefinition) {
		css_error code;
		css_stylesheet *sheet;
		size_t size;

		css_stylesheet_params params;
		params.params_version = CSS_STYLESHEET_PARAMS_VERSION_1;
		params.level = CSS_LEVEL_3;
		params.charset = NULL;
		params.url = "blah";
		params.title = "title";
		params.allow_quirks = false;
		params.inline_style = false;
		params.resolve = cssResolveUrl;
		params.resolve_pw = NULL;
		params.import = NULL;
		params.import_pw = NULL;
		params.color = NULL;
		params.color_pw = NULL;
		params.font = NULL;
		params.font_pw = NULL;

		code = css_stylesheet_create(&params, cssReallocate, NULL, &sheet);
		if (code != CSS_OK)
			debug::error("could not create stylesheet");

		/* parse CSS data */
		const char* data = cssDefinition.c_str();
		code = css_stylesheet_append_data(sheet, (const uint8_t *) data,
		                                  sizeof data);
		if (code != CSS_OK && code != CSS_NEEDDATA)
			debug::error("could not append data to stylesheet");
		code = css_stylesheet_data_done(sheet);
		if (code != CSS_OK)
			debug::error("stylesheet has empty data");
		code = css_stylesheet_size(sheet, &size);
		if (code != CSS_OK)
			debug::error("could not retreive stylesheet size");
		printf("appended data, size now %zu\n", size);
	}
};

}

}

}

#endif // CSSLOADABLE_H
