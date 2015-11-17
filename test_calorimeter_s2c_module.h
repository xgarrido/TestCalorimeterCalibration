// -*- mode: c++ ; -*-
/** \file falaise/snemo/processing/test_calorimeter_s2c_module.h
 * Author(s) :    Arnaud Huber <huber@cenbg.in2p3.fr>
 * Creation date: 2015-10-23
 * Last modified: 2015-10-23
 *
 * License:
 *
 * Description:
 *
 *   Test simulation data processor for calorimeter MC hits using a "mock"
 *   database file
 *
 * History:
 *
 */

#ifndef FALAISE_SNEMO_PROCESSING_TEST_CALORIMETER_S2C_MODULE_H
#define FALAISE_SNEMO_PROCESSING_TEST_CALORIMETER_S2C_MODULE_H 1

// Standard library:
#include <string>
#include <map>
#include <vector>

// Third party:
// - Bayeux/mygsl:
#include <mygsl/rng.h>
// - Bayeux/geomtools:
#include <geomtools/geom_id.h>
// - Bayeux/dpp:
#include <dpp/base_module.h>

// This project :
#include <falaise/snemo/datamodels/calibrated_data.h>
#include <falaise/snemo/processing/calorimeter_regime.h>

namespace geomtools {
  class manager;
}

namespace mctools {
  class simulated_data;
}

namespace snemo {

  namespace processing {

    /// \brief A test calibration for SuperNEMO calorimeter hits
    class test_calorimeter_s2c_module : public dpp::base_module
    {
    public:

      /// Dictionary of calorimeter regime objects associated to collection of calorimeter-like hits
      typedef std::map<geomtools::geom_id, calorimeter_regime> calorimeter_regime_col_type;

      /// Setting geometry manager
      void set_geom_manager(const geomtools::manager & gmgr_);

      /// Getting geometry manager
      const geomtools::manager & get_geom_manager() const;

      /// Set the external PRNG
      void set_external_random(mygsl::rng & rng_);

      /// Reset the external PRNG
      void reset_external_random();

      /// Check if the module use an external PRNG
      bool has_external_random() const;

      /// Constructor
      test_calorimeter_s2c_module(datatools::logger::priority = datatools::logger::PRIO_FATAL);

      /// Destructor
      virtual ~test_calorimeter_s2c_module();

      /// Initialization
      virtual void initialize(const datatools::properties  & setup_,
                              datatools::service_manager   & service_manager_,
                              dpp::module_handle_dict_type & module_dict_);

      /// Reset
      virtual void reset();

      /// Data record processing
      virtual process_status process(datatools::things & data_);

    protected:

      /// Set default attributes values
      void _set_defaults();

      /// Parse a database file
      void _parse_database_file(const std::string & db_path_);

      /// Getting random number generator
      mygsl::rng & _get_random();

      /// Digitize calorimeter hits
      void _process_calorimeter_digitization
      (const mctools::simulated_data & simulated_data_,
       snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & calibrated_calorimeter_hits_);

      /// Calibrate calorimeter hits (energy/time resolution spread)
      void _process_calorimeter_calibration
      (snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & calorimeter_hits_);

      /// Apply basic trigger effect
      void _process_calorimeter_trigger
      (snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & calorimeter_hits_);

      /// Main process function
      void _process
      (const mctools::simulated_data & simulated_data_,
       snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & calibrated_calorimeter_hits_);

    private:

      const geomtools::manager *  _geom_manager_;        //!< The geometry manager
      mygsl::rng                  _random_;              //!< PRN generator
      mygsl::rng *                _external_random_;     //!< external PRN generator
      std::vector<std::string>    _hit_categories_;      //!< Calorimeter hit categories
      calorimeter_regime_col_type _calorimeter_regimes_; //!< Calorimeter regime tools
      std::string                 _SD_label_;            //!< The label of the simulated data bank
      std::string                 _CD_label_;            //!< The label of the calibrated data bank
      std::string                 _Geo_label_;           //!< The label of the geometry service
      double                      _cluster_time_width_;  //!< Time width of a calo cluster
      bool                        _alpha_quenching_;     //!< Flag to (dis)activate the alpha quenching
      bool                        _store_mc_hit_id_;     //!< The flag to reference MC true hit

      // Macro to automate the registration of the module :
      DPP_MODULE_REGISTRATION_INTERFACE(test_calorimeter_s2c_module);

    };

  } // end of namespace processing

} // end of namespace snemo

/***************************
 * OCD support : interface *
 ***************************/

#include <datatools/ocd_macros.h>

// @arg snemo::processing::test_calorimeter_s2c_module the name the registered class
DOCD_CLASS_DECLARATION(snemo::processing::test_calorimeter_s2c_module)

#endif // FALAISE_SNEMO_PROCESSING_TEST_CALORIMETER_S2C_MODULE_H

// end of falaise/snemo/processing/test_calorimeter_s2c_module.h
