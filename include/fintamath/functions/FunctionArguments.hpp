#pragma once

namespace fintamath {

class IMathObject;

using ArgumentsRefVector = std::vector<std::reference_wrapper<const IMathObject>>;
using ArgumentsPtrVector = std::vector<std::shared_ptr<IMathObject>>;
using ArgumentsTypesVector = std::vector<std::reference_wrapper<const std::type_info>>;

}
