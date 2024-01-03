/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "NOD_rna_define.hh"

#include "UI_interface.hh"
#include "UI_resources.hh"

#include "RNA_enum_types.hh"

#include "node_geometry_util.hh"

namespace blender::nodes::node_geo_separate_geometry_cc {

NODE_STORAGE_FUNCS(NodeGeometrySeparateGeometry)

static void node_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::Geometry>("Geometry");
  b.add_input<decl::Bool>("Selection")
      .default_value(true)
      .hide_value()
      .field_on_all()
      .description("The parts of the geometry that go into the first output");
  b.add_output<decl::Geometry>("Selection")
      .propagate_all()
      .description("The parts of the geometry in the selection");
  b.add_output<decl::Geometry>("Inverted")
      .propagate_all()
      .description("The parts of the geometry not in the selection");
}

static void node_layout(uiLayout *layout, bContext * /*C*/, PointerRNA *ptr)
{
  uiItemR(layout, ptr, "domain", UI_ITEM_NONE, "", ICON_NONE);
}

static void node_init(bNodeTree * /*tree*/, bNode *node)
{
  NodeGeometrySeparateGeometry *data = MEM_cnew<NodeGeometrySeparateGeometry>(__func__);
  data->domain = int8_t(AttrDomain::Point);
  node->storage = data;
}

static void node_geo_exec(GeoNodeExecParams params)
{
  GeometrySet geometry_set = params.extract_input<GeometrySet>("Geometry");

  const Field<bool> selection_field = params.extract_input<Field<bool>>("Selection");

  const NodeGeometrySeparateGeometry &storage = node_storage(params.node());
  const AttrDomain domain = AttrDomain(storage.domain);

  auto separate_geometry_maybe_recursively =
      [&](GeometrySet &geometry_set,
          const Field<bool> &selection,
          const AnonymousAttributePropagationInfo &propagation_info) {
        bool is_error;
        if (domain == AttrDomain::Instance) {
          /* Only delete top level instances. */
          separate_geometry(geometry_set,
                            domain,
                            GEO_NODE_DELETE_GEOMETRY_MODE_ALL,
                            selection,
                            propagation_info,
                            is_error);
        }
        else {
          geometry_set.modify_geometry_sets([&](GeometrySet &geometry_set) {
            separate_geometry(geometry_set,
                              domain,
                              GEO_NODE_DELETE_GEOMETRY_MODE_ALL,
                              selection,
                              propagation_info,
                              is_error);
          });
        }
      };

  GeometrySet second_set(geometry_set);
  if (params.output_is_required("Selection")) {
    separate_geometry_maybe_recursively(
        geometry_set, selection_field, params.get_output_propagation_info("Selection"));
    params.set_output("Selection", std::move(geometry_set));
  }
  if (params.output_is_required("Inverted")) {
    separate_geometry_maybe_recursively(second_set,
                                        fn::invert_boolean_field(selection_field),
                                        params.get_output_propagation_info("Inverted"));
    params.set_output("Inverted", std::move(second_set));
  }
}

static void node_rna(StructRNA *srna)
{
  RNA_def_node_enum(srna,
                    "domain",
                    "Domain",
                    "Which domain to separate on",
                    rna_enum_attribute_domain_without_corner_items,
                    NOD_storage_enum_accessors(domain),
                    int(AttrDomain::Point));
}

static void node_register()
{
  static bNodeType ntype;

  geo_node_type_base(&ntype, GEO_NODE_SEPARATE_GEOMETRY, "Separate Geometry", NODE_CLASS_GEOMETRY);

  node_type_storage(&ntype,
                    "NodeGeometrySeparateGeometry",
                    node_free_standard_storage,
                    node_copy_standard_storage);

  ntype.initfunc = node_init;

  ntype.declare = node_declare;
  ntype.geometry_node_execute = node_geo_exec;
  ntype.draw_buttons = node_layout;
  nodeRegisterType(&ntype);

  node_rna(ntype.rna_ext.srna);
}
NOD_REGISTER_NODE(node_register)

}  // namespace blender::nodes::node_geo_separate_geometry_cc
