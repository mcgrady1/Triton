//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#ifndef TRITON_PATHMANAGER_H
#define TRITON_PATHMANAGER_H

#include <vector>

#include "instruction.hpp"
#include "pathConstraint.hpp"
#include "symbolicExpression.hpp"
#include "tritonTypes.hpp"



//! The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! The Engines namespace
  namespace engines {
  /*!
   *  \ingroup triton
   *  \addtogroup engines
   *  @{
   */

    //! The Symbolic Execution namespace
    namespace symbolic {
    /*!
     *  \ingroup engines
     *  \addtogroup symbolic
     *  @{
     */

      /*! \class PathManager
          \brief The path manager class. */
      class PathManager {
        protected:
          //! \brief The logical conjunction vector of path constraints.
          std::vector<triton::engines::symbolic::PathConstraint> pathConstraints;


        public:
          //! Constructor.
          PathManager();

          //! Constructor by copy.
          PathManager(const PathManager& copy);

          //! Destructore.
          ~PathManager();

          //! Copies a PathManager.
          void copy(const PathManager& other);

          //! Returns the logical conjunction vector of path constraints.
          const std::vector<triton::engines::symbolic::PathConstraint>& getPathConstraints(void) const;

          //! Returns the logical conjunction AST of path constraints.
          triton::ast::AbstractNode* getPathConstraintsAst(void) const;

          //! Returns the number of constraints.
          triton::usize getNumberOfPathConstraints(void) const;

          //! Adds a path constraint.
          void addPathConstraint(const triton::arch::Instruction& inst, triton::engines::symbolic::SymbolicExpression* expr);

          //! Clears the logical conjunction vector of path constraints.
          void clearPathConstraints(void);

          //! Copies a PathManager.
          void operator=(const PathManager& other);
      };

    /*! @} End of symbolic namespace */
    };
  /*! @} End of engines namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITON_PATHMANAGER_H */

