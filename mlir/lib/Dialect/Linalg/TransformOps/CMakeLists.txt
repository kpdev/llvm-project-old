add_mlir_dialect_library(MLIRLinalgTransformOps
  LinalgTransformOps.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/Linalg/TransformOps

  DEPENDS
  MLIRLinalgTransformOpsIncGen

  LINK_LIBS PUBLIC
  MLIRAffineDialect
  MLIRArithDialect
  MLIRFuncDialect
  MLIRIR
  MLIRLinalgDialect
  MLIRLinalgTransforms
  MLIRParser
  MLIRPDLDialect
  MLIRSCFDialect
  MLIRSideEffectInterfaces
  MLIRTransformDialect
  MLIRTransformDialectUtils
  MLIRVectorTransforms
  )
