local list = {
	'wglCreateContextAttribsARB',
	'wglSwapIntervalEXT'
}

for i, entry in ipairs(list) do
	list[i] = {
		name = entry,
		type = 'PFN' .. entry:upper() .. 'PROC'
	}
end

io.write([[
#ifndef VIDEO_OGL_H_
#define VIDEO_OGL_H_
#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>

]])

for _, entry in ipairs(list) do
	io.write(('extern %s video_%s;\n'):format(entry.type, entry.name))
end

io.write('\n')

for _, entry in ipairs(list) do
	io.write(('#define %s video_%s\n'):format(entry.name, entry.name))
end

io.write([[

void video_ogl_init();

#endif

#ifdef VIDEO_OGL_BUILD

]])

for _, entry in ipairs(list) do
	io.write(('%s video_%s;\n'):format(entry.type, entry.name))
end

io.write([[

static PROC ogl_addr(const char* name) {
	PROC proc = wglGetProcAddress(name);
	if (proc == NULL) {
		MessageBoxA(NULL, name, NULL, MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	return proc;
}

void video_ogl_init() {
]])

for _, entry in ipairs(list) do
	io.write(('\tvideo_%s = (%s)ogl_addr("%s");\n'):format(
		entry.name,
		entry.type,
		entry.name
	))
end

io.write([[
}

#endif
]])