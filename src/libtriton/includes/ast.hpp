//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef TRITON_AST_H
#define TRITON_AST_H

#include <list>
#include <map>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "astVisitor.hpp"
#include "tritonTypes.hpp"



//! \module The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! \module The SMT2-Lib namespace
  namespace ast {
  /*!
   *  \ingroup triton
   *  \addtogroup ast
   *  @{
   */

    /*! Enumerates all kinds of node. Must be prime numbers. */
    enum kind_e {
      UNDEFINED_NODE = 0,             /*!< Unknown node */
      ASSERT_NODE = 2,                /*!< (assert x) */
      BVADD_NODE = 3,                 /*!< (bvadd x y) */
      BVAND_NODE = 5,                 /*!< (bvand x y) */
      BVASHR_NODE = 7,                /*!< (bvashr x y) */
      BVDECL_NODE = 11,               /*!< (_ BitVec x) */
      BVLSHR_NODE = 13,               /*!< (bvlshr x y) */
      BVMUL_NODE = 17,                /*!< (bvmul x y) */
      BVNAND_NODE = 19,               /*!< (bvnand x y) */
      BVNEG_NODE = 23,                /*!< (bvneg x) */
      BVNOR_NODE = 29,                /*!< (bvnor x y) */
      BVNOT_NODE = 31,                /*!< (bvnot x) */
      BVOR_NODE = 37,                 /*!< (bvor x y) */
      BVROL_NODE = 41,                /*!< ((_ rotate_left x) y) */
      BVROR_NODE = 43,                /*!< ((_ rotate_right x) y) */
      BVSDIV_NODE = 47,               /*!< (bvsdiv x y) */
      BVSGE_NODE = 53,                /*!< (bvsge x y) */
      BVSGT_NODE = 59,                /*!< (bvsgt x y) */
      BVSHL_NODE = 61,                /*!< (bvshl x y) */
      BVSLE_NODE = 67,                /*!< (bvslr x y) */
      BVSLT_NODE = 71,                /*!< (bvslt x y) */
      BVSMOD_NODE = 73,               /*!< (bvsmod x y) */
      BVSREM_NODE = 79,               /*!< (bvsrem x y) */
      BVSUB_NODE = 83,                /*!< (bvsub x y) */
      BVUDIV_NODE = 89,               /*!< (bvudiv x y) */
      BVUGE_NODE = 97,                /*!< (bvuge x y) */
      BVUGT_NODE = 101,               /*!< (bvugt x y) */
      BVULE_NODE = 103,               /*!< (bvule x y) */
      BVULT_NODE = 107,               /*!< (bvult x y) */
      BVUREM_NODE = 109,              /*!< (bvurem x y) */
      BVXNOR_NODE = 113,              /*!< (bvxnor x y) */
      BVXOR_NODE = 127,               /*!< (bvxor x y) */
      BV_NODE = 131,                  /*!< (_ bvx y) */
      COMPOUND_NODE = 139,            /*!< Coumpound of several nodes */
      CONCAT_NODE = 149,              /*!< (concat x y z ...) */
      DECIMAL_NODE = 151,             /*!< Decimal node */
      DECLARE_FUNCTION_NODE = 157,    /*!< (declare-fun x () (_ BitVec y)) */
      DISTINCT_NODE = 163,            /*!< (distinct x y) */
      EQUAL_NODE = 167,               /*!< (= x y) */
      EXTRACT_NODE = 173,             /*!< ((_ extract x y) z) */
      FUNCTION_NODE = 179,            /*!< (define-fun w (x) y z) */
      ITE_NODE = 181,                 /*!< (ite x y z) */
      LAND_NODE = 191,                /*!< (and x y) */
      LET_NODE = 193,                 /*!< (let ((x y)) z) */
      LNOT_NODE = 197,                /*!< (and x y) */
      LOR_NODE = 199,                 /*!< (or x y) */
      PARAM_NODE = 211,               /*!< (x y) */
      REFERENCE_NODE = 223,           /*!< Reference node */
      STRING_NODE = 227,              /*!< String node */
      SX_NODE = 229,                  /*!< ((_ sign_extend x) y) */
      VARIABLE_NODE = 233,            /*!< Variable node */
      ZX_NODE = 239                   /*!< ((_ zero_extend x) y) */
    };


    //! Abstract node
    class smtAstAbstractNode {
      protected:
        //! The kind of the node.
        enum kind_e kind;

        //! The childs of the node.
        std::vector<smtAstAbstractNode*> childs;

        //! The size of the node.
        triton::uint32 size;

      public:
        //! Constructor.
        smtAstAbstractNode(enum kind_e kind);

        //! Constructor by copy.
        smtAstAbstractNode(const smtAstAbstractNode& copy);

        //! Constructor.
        smtAstAbstractNode();

        //! Destructor.
        virtual ~smtAstAbstractNode();

        //! Returns the kind of the node.
        enum kind_e getKind(void);

        //! Returns the size of the node.
        triton::uint32 getBitvectorSize(void);

        //! Returns the vector mask according the size of the node.
        triton::uint512 getBitvectorMask(void);

        //! Returns the childs of the node.
        std::vector<smtAstAbstractNode*>& getChilds(void);

        //! Sets the size of the node.
        void setBitvectorSize(triton::uint32 size);

        //! Adds a child.
        void addChild(smtAstAbstractNode* child);

        //! Entry point for a visitor.
        virtual void accept(AstVisitor& v) = 0;

        //! Returns the has of the tree. The hash is computed recursively on the whole tree.
        virtual triton::uint512 hash(triton::uint32 deep) = 0;
    };


    //! (assert <expr1>) node
    class smtAstAssertNode : public smtAstAbstractNode {
      public:
        smtAstAssertNode(smtAstAbstractNode* expr);
        smtAstAssertNode(const smtAstAssertNode& copy);
        ~smtAstAssertNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvadd <expr1> <expr2>) node
    class smtAstBvaddNode : public smtAstAbstractNode {
      public:
        smtAstBvaddNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvaddNode(const smtAstBvaddNode& copy);
        ~smtAstBvaddNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvand <expr1> <expr2>) node
    class smtAstBvandNode : public smtAstAbstractNode {
      public:
        smtAstBvandNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvandNode(const smtAstBvandNode& copy);
        ~smtAstBvandNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvashr <expr1> <expr2>) node
    class smtAstBvashrNode : public smtAstAbstractNode {
      public:
        smtAstBvashrNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvashrNode(const smtAstBvashrNode& copy);
        ~smtAstBvashrNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (_ BitVec x) node
    class smtAstBvdeclNode : public smtAstAbstractNode {
      public:
        smtAstBvdeclNode(triton::uint32 size);
        smtAstBvdeclNode(const smtAstBvdeclNode& copy);
        ~smtAstBvdeclNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvlshr <expr1> <expr2>) node
    class smtAstBvlshrNode : public smtAstAbstractNode {
      public:
        smtAstBvlshrNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvlshrNode(const smtAstBvlshrNode& copy);
        ~smtAstBvlshrNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvmul <expr1> <expr2>) node
    class smtAstBvmulNode : public smtAstAbstractNode {
      public:
        smtAstBvmulNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvmulNode(const smtAstBvmulNode& copy);
        ~smtAstBvmulNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvnand <expr1> <expr2>) node
    class smtAstBvnandNode : public smtAstAbstractNode {
      public:
        smtAstBvnandNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvnandNode(const smtAstBvnandNode& copy);
        ~smtAstBvnandNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvneg <expr>) node
    class smtAstBvnegNode : public smtAstAbstractNode {
      public:
        smtAstBvnegNode(smtAstAbstractNode* expr);
        smtAstBvnegNode(const smtAstBvnegNode& copy);
        ~smtAstBvnegNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvnor <expr1> <expr2>) node
    class smtAstBvnorNode : public smtAstAbstractNode {
      public:
        smtAstBvnorNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvnorNode(const smtAstBvnorNode& copy);
        ~smtAstBvnorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvnot <expr>) node
    class smtAstBvnotNode : public smtAstAbstractNode {
      public:
        smtAstBvnotNode(smtAstAbstractNode* expr1);
        smtAstBvnotNode(const smtAstBvnotNode& copy);
        ~smtAstBvnotNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvor <expr1> <expr2>) node
    class smtAstBvorNode : public smtAstAbstractNode {
      public:
        smtAstBvorNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvorNode(const smtAstBvorNode& copy);
        ~smtAstBvorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! ((_ rotate_left rot) expr) node
    class smtAstBvrolNode : public smtAstAbstractNode {
      public:
        smtAstBvrolNode(triton::uint32 rot, smtAstAbstractNode* expr);
        smtAstBvrolNode(smtAstAbstractNode* rot, smtAstAbstractNode* expr);
        smtAstBvrolNode(const smtAstBvrolNode& copy);
        ~smtAstBvrolNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! ((_ rotate_right rot) expr) node
    class smtAstBvrorNode : public smtAstAbstractNode {
      public:
        smtAstBvrorNode(triton::uint32 rot, smtAstAbstractNode* expr);
        smtAstBvrorNode(smtAstAbstractNode* rot, smtAstAbstractNode* expr);
        smtAstBvrorNode(const smtAstBvrorNode& copy);
        ~smtAstBvrorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsdiv <expr1> <expr2>) node
    class smtAstBvsdivNode : public smtAstAbstractNode {
      public:
        smtAstBvsdivNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsdivNode(const smtAstBvsdivNode& copy);
        ~smtAstBvsdivNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsge <expr1> <expr2>) node
    class smtAstBvsgeNode : public smtAstAbstractNode {
      public:
        smtAstBvsgeNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsgeNode(const smtAstBvsgeNode& copy);
        ~smtAstBvsgeNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsgt <expr1> <expr2>) node
    class smtAstBvsgtNode : public smtAstAbstractNode {
      public:
        smtAstBvsgtNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsgtNode(const smtAstBvsgtNode& copy);
        ~smtAstBvsgtNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvshl <expr1> <expr2>) node
    class smtAstBvshlNode : public smtAstAbstractNode {
      public:
        smtAstBvshlNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvshlNode(const smtAstBvshlNode& copy);
        ~smtAstBvshlNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsle <expr1> <expr2>) node
    class smtAstBvsleNode : public smtAstAbstractNode {
      public:
        smtAstBvsleNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsleNode(const smtAstBvsleNode& copy);
        ~smtAstBvsleNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvslt <expr1> <expr2>) node
    class smtAstBvsltNode : public smtAstAbstractNode {
      public:
        smtAstBvsltNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsltNode(const smtAstBvsltNode& copy);
        ~smtAstBvsltNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsmod <expr1> <expr2>) node
    class smtAstBvsmodNode : public smtAstAbstractNode {
      public:
        smtAstBvsmodNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsmodNode(const smtAstBvsmodNode& copy);
        ~smtAstBvsmodNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsrem <expr1> <expr2>) node
    class smtAstBvsremNode : public smtAstAbstractNode {
      public:
        smtAstBvsremNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsremNode(const smtAstBvsremNode& copy);
        ~smtAstBvsremNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvsub <expr1> <expr2>) node
    class smtAstBvsubNode : public smtAstAbstractNode {
      public:
        smtAstBvsubNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvsubNode(const smtAstBvsubNode& copy);
        ~smtAstBvsubNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvudiv <expr1> <expr2>) node
    class smtAstBvudivNode : public smtAstAbstractNode {
      public:
        smtAstBvudivNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvudivNode(const smtAstBvudivNode& copy);
        ~smtAstBvudivNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvuge <expr1> <expr2>) node
    class smtAstBvugeNode : public smtAstAbstractNode {
      public:
        smtAstBvugeNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvugeNode(const smtAstBvugeNode& copy);
        ~smtAstBvugeNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvugt <expr1> <expr2>) node
    class smtAstBvugtNode : public smtAstAbstractNode {
      public:
        smtAstBvugtNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvugtNode(const smtAstBvugtNode& copy);
        ~smtAstBvugtNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvule <expr1> <expr2>) node
    class smtAstBvuleNode : public smtAstAbstractNode {
      public:
        smtAstBvuleNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvuleNode(const smtAstBvuleNode& copy);
        ~smtAstBvuleNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvult <expr1> <expr2>) node
    class smtAstBvultNode : public smtAstAbstractNode {
      public:
        smtAstBvultNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvultNode(const smtAstBvultNode& copy);
        ~smtAstBvultNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvurem <expr1> <expr2>) node
    class smtAstBvuremNode : public smtAstAbstractNode {
      public:
        smtAstBvuremNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvuremNode(const smtAstBvuremNode& copy);
        ~smtAstBvuremNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvxnor <expr1> <expr2>) node
    class smtAstBvxnorNode : public smtAstAbstractNode {
      public:
        smtAstBvxnorNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvxnorNode(const smtAstBvxnorNode& copy);
        ~smtAstBvxnorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (bvxor <expr1> <expr2>) node
    class smtAstBvxorNode : public smtAstAbstractNode {
      public:
        smtAstBvxorNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstBvxorNode(const smtAstBvxorNode& copy);
        ~smtAstBvxorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (_ bv<value> <size>) node
    class smtAstBvNode : public smtAstAbstractNode {
      public:
        smtAstBvNode(triton::uint128 value, triton::uint32 size);
        smtAstBvNode(const smtAstBvNode& copy);
        ~smtAstBvNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! compound node
    class smtAstCompoundNode : public smtAstAbstractNode {
      public:
        smtAstCompoundNode(std::vector<smtAstAbstractNode*> exprs);
        smtAstCompoundNode(const smtAstCompoundNode& copy);
        ~smtAstCompoundNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (concat <expr1> <expr2> ...) node
    class smtAstConcatNode : public smtAstAbstractNode {
      public:
        smtAstConcatNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstConcatNode(std::vector<smtAstAbstractNode* > exprs);
        smtAstConcatNode(std::list<smtAstAbstractNode* > exprs);
        smtAstConcatNode(const smtAstConcatNode& copy);
        ~smtAstConcatNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! Decimal node
    class smtAstDecimalNode : public smtAstAbstractNode {
      protected:
        triton::uint128 value;

      public:
        smtAstDecimalNode(triton::uint128 value);
        smtAstDecimalNode(const smtAstDecimalNode& copy);
        ~smtAstDecimalNode();

        triton::uint128 getValue(void);
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (declare-fun <name> () bvDecl) node
    class smtAstDeclareFunctionNode : public smtAstAbstractNode {
      public:
        smtAstDeclareFunctionNode(std::string name, smtAstAbstractNode* bvDecl);
        smtAstDeclareFunctionNode(const smtAstDeclareFunctionNode& copy);
        ~smtAstDeclareFunctionNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (distinct <expr1> <expr2> ...) node
    class smtAstDistinctNode : public smtAstAbstractNode {
      public:
        smtAstDistinctNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstDistinctNode(const smtAstDistinctNode& copy);
        ~smtAstDistinctNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (= <expr1> <expr2> ...) node
    class smtAstEqualNode : public smtAstAbstractNode {
      public:
        smtAstEqualNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstEqualNode(const smtAstEqualNode& copy);
        ~smtAstEqualNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! ((_ extract <high> <low>) <expr>) node
    class smtAstExtractNode : public smtAstAbstractNode {
      public:
        smtAstExtractNode(triton::uint32 high, triton::uint32 low, smtAstAbstractNode* expr);
        smtAstExtractNode(const smtAstExtractNode& copy);
        ~smtAstExtractNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (ite ifExpr thenExpr elseExpr)
    class smtAstIteNode : public smtAstAbstractNode {
      public:
        smtAstIteNode(smtAstAbstractNode* ifExpr, smtAstAbstractNode* thenExpr, smtAstAbstractNode* elseExpr);
        smtAstIteNode(const smtAstIteNode& copy);
        ~smtAstIteNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (and <expr1> <expr2>)
    class smtAstLandNode : public smtAstAbstractNode {
      public:
        smtAstLandNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstLandNode(const smtAstLandNode& copy);
        ~smtAstLandNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (let ((<alias> <expr2>)) <expr3>)
    class smtAstLetNode : public smtAstAbstractNode {
      public:
        smtAstLetNode(std::string alias, smtAstAbstractNode* expr2, smtAstAbstractNode* expr3);
        smtAstLetNode(const smtAstLetNode& copy);
        ~smtAstLetNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (lnot <expr>)
    class smtAstLnotNode : public smtAstAbstractNode {
      public:
        smtAstLnotNode(smtAstAbstractNode* expr);
        smtAstLnotNode(const smtAstLnotNode& copy);
        ~smtAstLnotNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! (or <expr1> <expr2>)
    class smtAstLorNode : public smtAstAbstractNode {
      public:
        smtAstLorNode(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);
        smtAstLorNode(const smtAstLorNode& copy);
        ~smtAstLorNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! Reference node
    class smtAstReferenceNode : public smtAstAbstractNode {
      protected:
        triton::__uint value;

      public:
        smtAstReferenceNode(triton::__uint value);
        smtAstReferenceNode(const smtAstReferenceNode& copy);
        ~smtAstReferenceNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);

        triton::__uint getValue(void);
    };


    //! String node
    class smtAstStringNode : public smtAstAbstractNode {
      protected:
        std::string value;

      public:
        smtAstStringNode(std::string value);
        smtAstStringNode(const smtAstStringNode& copy);
        ~smtAstStringNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);

        std::string getValue(void);
    };


    //! ((_ sign_extend sizeExt) <expr>) node
    class smtAstSxNode : public smtAstAbstractNode {
      public:
        smtAstSxNode(triton::uint32 sizeExt, smtAstAbstractNode* expr);
        smtAstSxNode(const smtAstSxNode& copy);
        ~smtAstSxNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! Variable node
    class smtAstVariableNode : public smtAstAbstractNode {
      protected:
        std::string value;

      public:
        smtAstVariableNode(std::string value);
        smtAstVariableNode(const smtAstVariableNode& copy);
        ~smtAstVariableNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);

        std::string getValue(void);
    };


    //! ((_ zero_extend sizeExt) <expr>) node
    class smtAstZxNode : public smtAstAbstractNode {
      public:
        smtAstZxNode(triton::uint32 sizeExt, smtAstAbstractNode* expr);
        smtAstZxNode(const smtAstZxNode& copy);
        ~smtAstZxNode();
        virtual void accept(AstVisitor& v);
        virtual triton::uint512 hash(triton::uint32 deep);
    };


    //! Displays the node in ast representation.
    std::ostream& operator<<(std::ostream& stream, smtAstAbstractNode* node);


    //! Compares two trees.
    bool operator==(smtAstAbstractNode& node1, smtAstAbstractNode& node2);


    //! ast C++ api - bv node builder
    smtAstAbstractNode* bv(triton::uint128 value, triton::uint32 size);

    //! ast C++ api - bvadd node builder
    smtAstAbstractNode* bvadd(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvand node builder
    smtAstAbstractNode* bvand(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvashr node builder
    smtAstAbstractNode* bvashr(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvdecl node builder
    smtAstAbstractNode* bvdecl(triton::uint32 size);

    //! ast C++ api - bvfalse node builder
    smtAstAbstractNode* bvfalse(void);

    //! ast C++ api - bvlshr node builder
    smtAstAbstractNode* bvlshr(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvmul node builder
    smtAstAbstractNode* bvmul(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvnand node builder
    smtAstAbstractNode* bvnand(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvneg node builder
    smtAstAbstractNode* bvneg(smtAstAbstractNode* expr);

    //! ast C++ api - bvnor node builder
    smtAstAbstractNode* bvnor(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvnot node builder
    smtAstAbstractNode* bvnot(smtAstAbstractNode* expr);

    //! ast C++ api - bvor node builder
    smtAstAbstractNode* bvor(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvrol node builder
    smtAstAbstractNode* bvrol(triton::uint32 rot, smtAstAbstractNode* expr);

    //! ast C++ api - bvrol node builder
    smtAstAbstractNode* bvrol(smtAstAbstractNode* rot, smtAstAbstractNode* expr);

    //! ast C++ api - bvror node builder
    smtAstAbstractNode* bvror(triton::uint32 rot, smtAstAbstractNode* expr);

    //! ast C++ api - bvror node builder
    smtAstAbstractNode* bvror(smtAstAbstractNode* rot, smtAstAbstractNode* expr);

    //! ast C++ api - bvsdiv node builder
    smtAstAbstractNode* bvsdiv(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsge node builder
    smtAstAbstractNode* bvsge(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsgt node builder
    smtAstAbstractNode* bvsgt(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvshl node builder
    smtAstAbstractNode* bvshl(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsle node builder
    smtAstAbstractNode* bvsle(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvslt node builder
    smtAstAbstractNode* bvslt(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsmod node builder
    smtAstAbstractNode* bvsmod(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsrem node builder
    smtAstAbstractNode* bvsrem(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvsub node builder
    smtAstAbstractNode* bvsub(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvtrue node builder
    smtAstAbstractNode* bvtrue(void);

    //! ast C++ api - bvudiv node builder
    smtAstAbstractNode* bvudiv(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvuge node builder
    smtAstAbstractNode* bvuge(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvugt node builder
    smtAstAbstractNode* bvugt(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvule node builder
    smtAstAbstractNode* bvule(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvult node builder
    smtAstAbstractNode* bvult(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvurem node builder
    smtAstAbstractNode* bvurem(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvxnor node builder
    smtAstAbstractNode* bvxnor(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - bvxor node builder
    smtAstAbstractNode* bvxor(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - compound node builder
    smtAstAbstractNode* compound(std::vector<smtAstAbstractNode* > exprs);

    //! ast C++ api - concat node builder
    smtAstAbstractNode* concat(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - concat node builder
    smtAstAbstractNode* concat(std::vector<smtAstAbstractNode* > exprs);

    //! ast C++ api - concat node builder
    smtAstAbstractNode* concat(std::list<smtAstAbstractNode* > exprs);

    //! ast C++ api - decimal node builder
    smtAstAbstractNode* decimal(triton::uint128 value);

    //! ast C++ api - declare node builder
    smtAstAbstractNode* declareFunction(std::string name, smtAstAbstractNode* bvDecl);

    //! ast C++ api - distinct node builder
    smtAstAbstractNode* distinct(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - equal node builder
    smtAstAbstractNode* equal(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - extract node builder
    smtAstAbstractNode* extract(triton::uint32 high, triton::uint32 low, smtAstAbstractNode* expr);

    //! ast C++ api - ite node builder
    smtAstAbstractNode* ite(smtAstAbstractNode* ifExpr, smtAstAbstractNode* thenExpr, smtAstAbstractNode* elseExpr);

    //! ast C++ api - land node builder
    smtAstAbstractNode* land(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - let node builder
    smtAstAbstractNode* let(std::string alias, smtAstAbstractNode* expr2, smtAstAbstractNode* expr3);

    //! ast C++ api - lnot node builder
    smtAstAbstractNode* lnot(smtAstAbstractNode* expr);

    //! ast C++ api - lor node builder
    smtAstAbstractNode* lor(smtAstAbstractNode* expr1, smtAstAbstractNode* expr2);

    //! ast C++ api - reference node builder
    smtAstAbstractNode* reference(triton::__uint value);

    //! ast C++ api - assert node builder
    smtAstAbstractNode* assert_(smtAstAbstractNode* expr);

    //! ast C++ api - string node builder
    smtAstAbstractNode* string(std::string value);

    //! ast C++ api - sx node builder
    smtAstAbstractNode* sx(triton::uint32 sizeExt, smtAstAbstractNode* expr);

    //! ast C++ api - variable node builder
    smtAstAbstractNode* variable(std::string variable);

    //! ast C++ api - zx node builder
    smtAstAbstractNode* zx(triton::uint32 sizeExt, smtAstAbstractNode* expr);

    //! ast C++ api - Duplicates the AST
    smtAstAbstractNode* newInstance(smtAstAbstractNode* node);

    //! Garbage collector - This container contains all allocated nodes.
    extern std::set<smtAstAbstractNode*> allocatedNodes;

    //! Garbage collector - Go through every allocated nodes and free them.
    void freeAllAstNodes(void);

    //! Garbage collector - Frees a set of nodes and removes them from the global container.
    void freeAstNodes(std::set<smtAstAbstractNode*>& nodes);

    //! Garbage collector - Extracts all unique nodes from a partial AST into the `uniqueNodes` set.
    void extractUniqueAstNodes(std::set<smtAstAbstractNode*>& uniqueNodes, smtAstAbstractNode* root);

    //! Garbage collector - Records the allocated node or returns the same node if it already exists inside the summaries.
    smtAstAbstractNode* recordNode(smtAstAbstractNode* node);

    //! Custom pow function for hash routine.
    triton::uint512 pow(triton::uint512 hash, triton::uint32 n);

    //! Custom rotate left function for hash routine.
    triton::uint512 rotl(triton::uint512 value, triton::uint32 shift);

  /*! @} End of ast namespace */
  };
/*! @} End of triton namespace */
};


#endif /* TRITON_AST_H */
