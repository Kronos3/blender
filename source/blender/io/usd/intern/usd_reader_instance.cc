<<<<<<< HEAD
/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2021 NVIDIA Corporation.
 * All rights reserved.
 */

#include "usd_reader_instance.h"

#include "BKE_object.hh"
#include "DNA_object_types.h"

#include <iostream>
=======
/* SPDX-FileCopyrightText: 2023 NVIDIA Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "usd_reader_instance.h"

#include "BKE_lib_id.h"
#include "BKE_object.hh"

#include "DNA_collection_types.h"
#include "DNA_object_types.h"
>>>>>>> main

namespace blender::io::usd {

USDInstanceReader::USDInstanceReader(const pxr::UsdPrim &prim,
                                     const USDImportParams &import_params,
                                     const ImportSettings &settings)
    : USDXformReader(prim, import_params, settings)
{
}

bool USDInstanceReader::valid() const
{
  return prim_.IsValid() && prim_.IsInstance();
}

void USDInstanceReader::create_object(Main *bmain, const double /* motionSampleTime */)
{
  this->object_ = BKE_object_add_only_object(bmain, OB_EMPTY, name_.c_str());
  this->object_->data = nullptr;
<<<<<<< HEAD
=======
  this->object_->instance_collection = nullptr;
>>>>>>> main
  this->object_->transflag |= OB_DUPLICOLLECTION;
}

void USDInstanceReader::set_instance_collection(Collection *coll)
{
<<<<<<< HEAD
  if (this->object_) {
=======
  if (this->object_ && this->object_->instance_collection != coll) {
    if (this->object_->instance_collection) {
      id_us_min(&this->object_->instance_collection->id);
      this->object_->instance_collection = nullptr;
    }
    id_us_plus(&coll->id);
>>>>>>> main
    this->object_->instance_collection = coll;
  }
}

pxr::SdfPath USDInstanceReader::proto_path() const
{
  if (pxr::UsdPrim proto = prim_.GetPrototype()) {
    return proto.GetPath();
  }

  return pxr::SdfPath();
}

}  // namespace blender::io::usd
