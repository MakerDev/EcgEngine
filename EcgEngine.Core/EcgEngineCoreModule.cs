using EcgEngine.Core.Dialogs.ViewModels;
using EcgEngine.Core.Dialogs.Views;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace EcgEngine.Core
{
    public class EcgEngineCoreModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {

        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            ConfigureDialogViewModelLocator();

            containerRegistry.RegisterDialog<ConfirmationDialog, ConfirmationDialogViewModel>();
            containerRegistry.RegisterDialog<MessageDialog, MessageDialogViewModel>();
        }

        private void ConfigureDialogViewModelLocator()
        {
            ViewModelLocationProvider.SetDefaultViewTypeToViewModelTypeResolver((viewType) =>
            {
                string replacement = ".";

                if (viewType.Name.Contains("Dialog"))
                {
                    replacement = ".Dialogs.";
                }

                var viewName = viewType.FullName.Replace(".ViewModels.", replacement);
                var viewAssemblyName = viewType.GetTypeInfo().Assembly.FullName;
                var viewModelName = $"{viewName}ViewModel, {viewAssemblyName}";
                return Type.GetType(viewModelName);
            });
        }
    }
}
