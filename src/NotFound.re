open Utils;

requireCSS("src/NotFound.css");

let notFoundImage = requireAssetURI("src/notfound404.png");

let component = ReasonReact.statelessComponent("NotFound");

let make = _children => {
  ...component,
  render: _self =>
    <MainLayout>
      <div className="NotFound_container">
        <div className="NotFound_image">
          <img alt="Page not found" src=notFoundImage />
        </div>
        <div className="NotFound_text">
          <span>
            (
              ReasonReact.string(
                "The page you're looking for can't be found. Go home by ",
              )
            )
          </span>
          <Link href="/"> (ReasonReact.string("clicking here!")) </Link>
        </div>
      </div>
    </MainLayout>,
};
