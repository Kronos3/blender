/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup editorui
 */

#pragma once

#include <memory>

#include "BLI_string_ref.hh"
#include "BLI_vector.hh"

#include "UI_resources.h"

namespace blender::nodes::geo_eval_log {
struct GeometryAttributeInfo;
}

struct bContext;
struct StructRNA;
struct uiBlock;
struct uiBut;
struct uiSearchItems;

namespace blender::ui {

class AbstractGridView;
class AbstractTreeView;

/**
 * An item in a breadcrumb-like context. Currently this struct is very simple, but more
 * could be added to it in the future, to support interactivity or tooltips, for example.
 */
struct ContextPathItem {
  /* Text to display in the UI. */
  std::string name;
  /* #BIFIconID */
  int icon;
  int icon_indicator_number;
};

void context_path_add_generic(Vector<ContextPathItem> &path,
                              StructRNA &rna_type,
                              void *ptr,
                              const BIFIconID icon_override = ICON_NONE);

void template_breadcrumbs(uiLayout &layout, Span<ContextPathItem> context_path);

void attribute_search_add_items(StringRefNull str,
                                bool can_create_attribute,
                                Span<const nodes::geo_eval_log::GeometryAttributeInfo *> infos,
                                uiSearchItems *items,
                                bool is_first);

}  // namespace blender::ui

void UI_but_func_set(uiBut *but, std::function<void(bContext &)> func);
void UI_but_func_pushed_state_set(uiBut *but, std::function<bool(const uiBut &)> func);

/**
 * Override this for all available view types.
 */
blender::ui::AbstractGridView *UI_block_add_view(
    uiBlock &block,
    blender::StringRef idname,
    std::unique_ptr<blender::ui::AbstractGridView> grid_view);
blender::ui::AbstractTreeView *UI_block_add_view(
    uiBlock &block,
    blender::StringRef idname,
    std::unique_ptr<blender::ui::AbstractTreeView> tree_view);
