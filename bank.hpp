#warning "obsolete"
#ifndef BANK_HPP
#define BANK_HPP

class program;
class parameter;

//-----------------------------------------------------------------------------
//! Bank base class.
//-----------------------------------------------------------------------------
class bank
{
friend class program;
  
public:
  bank(int32_t &nProg, int32_t &nParm, int32_t maxProg = 128, int32_t maxParm = 128);
  virtual ~bank();

  //! Load programs[program] into curProgram.
  void load_program(int32_t program);
  
  //! Store curProgram into programs[program].
  void store_program(int32_t program);
  
  //! Set name of curProgram.
  void set_program_name(const char *name);

  //! Get name of curProgram.
  void get_program_name(char *name) const;
  
  //! Add a parameter.
  float *add_parameter(parameter *p);
  
  //! Get number of parameters.
  int32_t num_params() const { return nParams; }

  void set_sarameter(int32_t index, float value);
  float get_parameter(int32_t index);

  void get_parameter_label(int32_t index, char *label) const { params[index]->getLabel(label); }
  void get_parameter_name(int32_t index, char *text) const { params[index]->getName(text); }
  float get_parameter_initial(int32_t index) const { return params[index]->getInitial(); }
  void get_parameter_display(int32_t index, char *text) const;
  
protected:
  int32_t m_maxparams;    //!< Maximum number of parameters.
  int32_t m_maxprograms;  //!< Maximum number of programs.
  int32_t &m_nparams;     //!< Current number of parameters.
  int32_t &m_nprograms;   //!< Current number of programs.

  program cur_program; //!< Current program.

  parameter **params;     //!< List of parameters.
  program **programs; //!< List of programs.
};

} // end namespace VST

//-----------------------------------------------------------------------------
#endif /* BANK_HPP */
