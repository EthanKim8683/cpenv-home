local root = vim.fn.fnamemodify(debug.getinfo(1, "S").source:sub(2), ":p:h")

require("luasnip.loaders.from_lua").lazy_load({
	paths = { root .. "/snippets" },
})
