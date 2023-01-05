#include "fintamath/numbers/NumberConstants.hpp"

#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {

const Integer ZERO = 0;

const Integer ONE = 1;

const Real E_NUM = RealImpl(default_ops::get_constant_e<RealImpl::Backend::backend_type>());

const Real PI_NUM = RealImpl(default_ops::get_constant_pi<RealImpl::Backend::backend_type>());

}
