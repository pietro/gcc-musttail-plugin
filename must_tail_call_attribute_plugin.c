#include "gcc-plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "stringpool.h"
#include "attribs.h"
#include "print-tree.h"

int plugin_is_GPL_compatible;

static struct plugin_info musttail_plugin_info = {
  .version = "0.0.1",
  .help = "Provides musttail attribute\n",
};

static struct attribute_spec musttail_attr = {
  .name = "musttail",
  .min_length = 0,
  .max_length = 0,
  .decl_required = true,
  .type_required = false,
  .function_type_required = false,
  .affects_type_identity = false,
  .handler = NULL,
  .exclude = NULL,
};

static void
register_attributes (void *event_data ATTRIBUTE_UNUSED,
		     void *data ATTRIBUTE_UNUSED)
{
  register_attribute (&musttail_attr);
}

tree
cb_walk_tree_fn (tree *tp, int *walk_subtrees ATTRIBUTE_UNUSED,
		 void *data ATTRIBUTE_UNUSED)
{
  if (TREE_CODE (*tp) != CALL_EXPR)
    return NULL_TREE;

  tree call_expr = *tp;

  CALL_EXPR_MUST_TAIL_CALL (call_expr) = 1;

  return NULL_TREE;
}

static void
musttail_pre_genericize_callback (void *event_data,
				  void *user_data ATTRIBUTE_UNUSED)
{
  tree fndecl = (tree) event_data;

  if (fndecl != NULL_TREE)
    {
      tree attrlist = DECL_ATTRIBUTES (fndecl);
      if (attrlist != NULL_TREE)
	{
	  tree attr;
	  for (attr = lookup_attribute ("musttail", attrlist);
	       attr != NULL_TREE;
	       attr = lookup_attribute ("musttail", TREE_CHAIN (attr)))
	    {
	      walk_tree (&DECL_SAVED_TREE (fndecl), cb_walk_tree_fn, NULL,
			 NULL);
	    }
	}
    }
}

int
plugin_init (struct plugin_name_args *plugin_info,
	     struct plugin_gcc_version *version)
{
  const char *plugin_name = plugin_info->base_name;

  if (!plugin_default_version_check (version, &gcc_version))
    return 1;

  register_callback (plugin_name, PLUGIN_INFO, NULL, &musttail_plugin_info);
  register_callback (plugin_name, PLUGIN_ATTRIBUTES, register_attributes, NULL);
  register_callback (plugin_info->base_name, PLUGIN_PRE_GENERICIZE,
		     musttail_pre_genericize_callback, NULL);

  return 0;
}
