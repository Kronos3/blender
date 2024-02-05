/* SPDX-FileCopyrightText: 2004-2022 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup freestyle
 */

#include "BPy_IncrementChainingTimeStampF1D.h"

#include "../../../view_map/Functions1D.h"
#include "../../BPy_Convert.h"
#include "../../BPy_IntegrationType.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace Freestyle;

///////////////////////////////////////////////////////////////////////////////////////////

//------------------------INSTANCE METHODS ----------------------------------

PyDoc_STRVAR(
    /* Wrap. */
    IncrementChainingTimeStampF1D___doc__,
    "Class hierarchy: :class:`freestyle.types.UnaryFunction1D` > "
    ":class:`freestyle.types.UnaryFunction1DVoid` > :class:`IncrementChainingTimeStampF1D`\n"
    "\n"
    ".. method:: __init__()\n"
    "\n"
    "   Builds an IncrementChainingTimeStampF1D object.\n"
    "\n"
    ".. method:: __call__(inter)\n"
    "\n"
    "   Increments the chaining time stamp of the Interface1D.\n"
    "\n"
    "   :arg inter: An Interface1D object.\n"
    "   :type inter: :class:`freestyle.types.Interface1D`\n");

static int IncrementChainingTimeStampF1D___init__(BPy_IncrementChainingTimeStampF1D *self,
                                                  PyObject *args,
                                                  PyObject *kwds)
{
  static const char *kwlist[] = {nullptr};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "", (char **)kwlist)) {
    return -1;
  }
  self->py_uf1D_void.uf1D_void = new Functions1D::IncrementChainingTimeStampF1D();
  return 0;
}

/*-----------------------BPy_IncrementChainingTimeStampF1D type definition ----------------------*/

PyTypeObject IncrementChainingTimeStampF1D_Type = {
    /*ob_base*/ PyVarObject_HEAD_INIT(nullptr, 0)
    /*tp_name*/ "IncrementChainingTimeStampF1D",
    /*tp_basicsize*/ sizeof(BPy_IncrementChainingTimeStampF1D),
    /*tp_itemsize*/ 0,
    /*tp_dealloc*/ nullptr,
    /*tp_vectorcall_offset*/ 0,
    /*tp_getattr*/ nullptr,
    /*tp_setattr*/ nullptr,
    /*tp_as_async*/ nullptr,
    /*tp_repr*/ nullptr,
    /*tp_as_number*/ nullptr,
    /*tp_as_sequence*/ nullptr,
    /*tp_as_mapping*/ nullptr,
    /*tp_hash*/ nullptr,
    /*tp_call*/ nullptr,
    /*tp_str*/ nullptr,
    /*tp_getattro*/ nullptr,
    /*tp_setattro*/ nullptr,
    /*tp_as_buffer*/ nullptr,
    /*tp_flags*/ Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    /*tp_doc*/ IncrementChainingTimeStampF1D___doc__,
    /*tp_traverse*/ nullptr,
    /*tp_clear*/ nullptr,
    /*tp_richcompare*/ nullptr,
    /*tp_weaklistoffset*/ 0,
    /*tp_iter*/ nullptr,
    /*tp_iternext*/ nullptr,
    /*tp_methods*/ nullptr,
    /*tp_members*/ nullptr,
    /*tp_getset*/ nullptr,
    /*tp_base*/ &UnaryFunction1DVoid_Type,
    /*tp_dict*/ nullptr,
    /*tp_descr_get*/ nullptr,
    /*tp_descr_set*/ nullptr,
    /*tp_dictoffset*/ 0,
    /*tp_init*/ (initproc)IncrementChainingTimeStampF1D___init__,
    /*tp_alloc*/ nullptr,
    /*tp_new*/ nullptr,
};

///////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
